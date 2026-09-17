/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */


#include "Core/Net/Rest/Gs2RestSession.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Misc/EngineVersionComparison.h"
#include "Core/Gs2Constant.h"
#include "Core/Model/Region.h"
#include "Core/Net/Rest/RestResponseState.h"
#include "Core/Net/Rest/Task/RestOpenTask.h"
#include "Core/Net/Rest/Task/RestCloseTask.h"
#include "Core/Net/Rest/Task/RestReOpenTask.h"

#include <atomic>

namespace Gs2::Core::Net::Rest
{
    namespace
    {
        /**
         * 応答が得られなかった要求を、接続段階の失敗かどうかで分類する。
         * ★UE 5.3 以前: DNS 失敗 / TCP 拒否だけが EHttpRequestStatus::Failed_ConnectionError（CurlHttp が
         *   "safe to retry" と註記する経路）。TLS 失敗や SetTimeout の満了は Failed になり区別できないので Other。
         * UE 5.4 以降: IHttpRequest::GetFailureReason() の ConnectionError / TimedOut を使う。
         */
        ERestTransportFailure ClassifyTransportFailure(const FHttpRequestPtr& Request)
        {
            if (!Request.IsValid())
            {
                return ERestTransportFailure::Other;
            }
#if UE_VERSION_OLDER_THAN(5, 4, 0)
            if (Request->GetStatus() == EHttpRequestStatus::Failed_ConnectionError)
            {
                return ERestTransportFailure::ConnectFailed;
            }
            return ERestTransportFailure::Other;
#else
            switch (Request->GetFailureReason())
            {
            case EHttpFailureReason::ConnectionError:
                return ERestTransportFailure::ConnectFailed;
            case EHttpFailureReason::TimedOut:
                return ERestTransportFailure::Timeout;
            default:
                return ERestTransportFailure::Other;
            }
#endif
        }

        /** 生成タスクの送信部と同じ形で 1 回だけ送る。TimeoutSec が正なら要求全体のタイムアウトを掛ける。 */
        FRestSessionResponse InvokeOnce(const FRestSessionRequest& Request, const float TimeoutSec)
        {
            const auto Completion = MakeShared<FRestResponseState, ESPMode::ThreadSafe>();
            const auto Failure = MakeShared<std::atomic<uint8>, ESPMode::ThreadSafe>(
                static_cast<uint8>(ERestTransportFailure::Other)
            );
            {
                const auto HttpRequest = FHttpModule::Get().CreateRequest();
                HttpRequest->OnProcessRequestComplete().BindLambda(
                    [Completion, Failure](FHttpRequestPtr CompletedRequest, FHttpResponsePtr Response, bool Successful)
                    {
                        if (Successful && Response.IsValid())
                        {
                            Failure->store(static_cast<uint8>(ERestTransportFailure::None));
                            Completion->Complete(Response->GetResponseCode(), Response->GetContentAsString());
                        }
                        else
                        {
                            Failure->store(static_cast<uint8>(ClassifyTransportFailure(CompletedRequest)));
                            Completion->Complete(999, FString());
                        }
                    }
                );
                HttpRequest->SetURL(Request.Url);
                HttpRequest->SetVerb(Request.Verb);
                for (const auto& Header : Request.Headers)
                {
                    HttpRequest->SetHeader(Header.Key, Header.Value);
                }
                if (Request.Body.IsSet())
                {
                    HttpRequest->SetContentAsString(Request.Body.GetValue());
                }
                if (TimeoutSec > 0.f)
                {
                    HttpRequest->SetTimeout(TimeoutSec);
                }
                HttpRequest->ProcessRequest();

                UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s] %s %s"),
                    ToCStr(Request.Verb),
                    ToCStr(Request.Url),
                    Request.Body.IsSet() ? ToCStr(Request.Body.GetValue()) : TEXT(""));
            }

            if (FPlatformTLS::GetCurrentThreadId() == GGameThreadId)
            {
                FHttpModule::Get().GetHttpManager().Flush(EHttpFlushReason::FullFlush);
            }
            else
            {
                while (!Completion->IsComplete())
                {
                    FPlatformProcess::Sleep(0.01f);
                }
            }

            FRestSessionResponse Response;
            Response.Url = Request.Url;
            if (!Completion->TryGetResponse(Response.ResponseCode, Response.ResponseBody))
            {
                Response.TransportFailure = ERestTransportFailure::Other;
                return Response;
            }
            Response.TransportFailure = static_cast<ERestTransportFailure>(Failure->load());
            return Response;
        }
    }

    FGs2RestSession::FGs2RestSession(
        const Model::FGs2CredentialPtr Credential
    ): CredentialValue(Credential), RegionValue(Model::ERegion::ApNorthEast1), OwnerIdValue(""), SteadyEndpointValue("")
    {
        
    }

    FGs2RestSession::FGs2RestSession(
        const FGs2RestSession& From
    ): CredentialValue(From.CredentialValue), RegionValue(From.RegionValue), OwnerIdValue(""), SteadyEndpointValue(From.SteadyEndpointValue)
    {
    }

    FGs2RestSession::FGs2RestSession(
        const Model::FGs2CredentialPtr Credential,
        const Model::ERegion Region
    ): CredentialValue(Credential), RegionValue(Region), OwnerIdValue(""), SteadyEndpointValue("")
    {
        
    }

    TSharedPtr<FAsyncTask<Task::FRestOpenTask>> FGs2RestSession::Open()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FRestOpenTask>>(SharedThis(this));
    }

    TSharedPtr<FAsyncTask<Task::FRestReOpenTask>> FGs2RestSession::ReOpen()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FRestReOpenTask>>(SharedThis(this));
    }

    TSharedPtr<FAsyncTask<Task::FRestCloseTask>> FGs2RestSession::Close()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FRestCloseTask>>(SharedThis(this));
    }

    void FGs2RestSession::SetSteadyEndpoint(const FString& SteadyEndpoint)
    {
        SteadyEndpointValue = FGs2Steady::NormalizeEndpoint(SteadyEndpoint);
        // ★生成タスクはセッションを見ずに FGs2Constant::EndpointHost を読むので、そこにも反映する。
        // アプリが自分で上書きしているときは何も書かない（静的な上書きが優先）。
        FGs2Constant::ApplySteadyEndpointHost(SteadyEndpointValue);
    }

    FString FGs2RestSession::SteadyEndpoint() const
    {
        return SteadyEndpointValue;
    }

    bool FGs2RestSession::HasSteadyEndpoint() const
    {
        return !SteadyEndpointValue.IsEmpty();
    }

    FString FGs2RestSession::EndpointHost(const FString& Service) const
    {
        // 優先順: アプリによる静的な上書き ＞ SteadyEndpoint ＞ 共有クラウドの既定値。
        FString Template = FGs2Constant::EndpointHost;
        if (!FGs2Constant::IsEndpointHostOverridden())
        {
            if (const auto Steady = FGs2Steady::RestTemplate(SteadyEndpointValue); !Steady.IsEmpty())
            {
                Template = Steady;
            }
        }
        const auto RegionString = RegionName();
        return Template
            .Replace(TEXT("{service}"), *Service)
            .Replace(TEXT("{region}"), *RegionString);
    }

    FRestSessionResponse FGs2RestSession::Send(const FRestSessionRequest& Request) const
    {
        const bool bViaSteady = FGs2Steady::IsSteadyUrl(SteadyEndpointValue, Request.Url);
        // ★UE には接続専用のタイムアウトが無い。要求全体の上限は冪等な動詞にだけ掛ける（POST / PUT は殺さない）。
        const float TimeoutSec = bViaSteady && Request.IsIdempotent() ? FGs2Steady::ConnectTimeoutSeconds : 0.f;

        auto Response = InvokeOnce(Request, TimeoutSec);
        if (bViaSteady && Response.TransportFailure == ERestTransportFailure::ConnectFailed)
        {
            // ★Steady の再送: 基点への接続段階の失敗（DNS / TCP 拒否。1 バイトも送っていない）だけ、同じ要求を
            // もう 1 回だけ送る。フリートが手放した IP に当たったとき、名前を引き直して別のノードへ着く機会を
            // 1 回だけ作る。送信後の失敗は届いたかもしれないので再送しない（非冪等要求の二重実行を作らない）。
            UE_LOG(Gs2Log, Warning, TEXT("steady endpoint connect failed, retrying once: %s"), ToCStr(Request.Url));
            Response = InvokeOnce(Request, TimeoutSec);
            Response.bRetried = true;
        }
        return Response;
    }

    FString FGs2RestSession::OwnerId() const
    {
        return OwnerIdValue;
    }

    void FGs2RestSession::SetOwnerId(FString OwnerId)
    {
        OwnerIdValue = OwnerId;
    }

    Model::ERegion FGs2RestSession::Region() const
    {
        return RegionValue;
    }

    Model::FGs2CredentialPtr FGs2RestSession::Credential() const
    {
        return CredentialValue;
    }

    FString FGs2RestSession::RegionName() const
    {
        switch (RegionValue)
        {
        case Model::ApNorthEast1:
            return "ap-northeast-1";
        case Model::UsEast1:
            return "us-east-1";
        case Model::EuWest1:
            return "eu-west-1";
        case Model::ApSouthEast1:
            return "ap-southeast-1";
        }
        return "unknown";
    }
}
