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

#include "Guild/Task/Rest/WithdrawalByUserIdTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Guild/Error/GuildMasterRequiredError.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Guild::Task::Rest
{
    FWithdrawalByUserIdTask::FWithdrawalByUserIdTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FWithdrawalByUserIdRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FWithdrawalByUserIdTask::FWithdrawalByUserIdTask(
        const FWithdrawalByUserIdTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FWithdrawalByUserIdTask::Action(
        const TSharedPtr<Result::FWithdrawalByUserIdResultPtr> Result
    )
    {

        if (this->Session->Credential()->ProjectToken().Len() == 0)
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FSessionNotOpenError>(Details);
        }

        auto Processing = true;
        int32 ResponseCode;
        FString ResponseBody;
        {
            const auto request = FHttpModule::Get().CreateRequest();
            request->OnProcessRequestComplete().BindLambda(
                [&Processing, &ResponseCode, &ResponseBody](FHttpRequestPtr _, FHttpResponsePtr Response, bool Successful)
                {
                    if (Successful) {
                        ResponseCode = Response->GetResponseCode();
                        ResponseBody = Response->GetContentAsString();
                    } else {
                        ResponseCode = 999;
                    }
                    Processing = false;
                }
            );
            auto Url = Core::FGs2Constant::EndpointHost
                .Replace(TEXT("{service}"), TEXT("guild"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/user/{userId}/joined/{guildModelName}/{guildName}");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );
            Url = Url.Replace(
                TEXT("{userId}"),
                !this->Request->GetUserId().IsSet() || this->Request->GetUserId().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetUserId())
            );
            Url = Url.Replace(
                TEXT("{guildModelName}"),
                !this->Request->GetGuildModelName().IsSet() || this->Request->GetGuildModelName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetGuildModelName())
            );
            Url = Url.Replace(
                TEXT("{guildName}"),
                !this->Request->GetGuildName().IsSet() || this->Request->GetGuildName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetGuildName())
            );

            TArray<FString> queryStrings;
            if (this->Request->GetContextStack().IsSet()) {
                queryStrings.Add("contextStack=" + FGenericPlatformHttp::UrlEncode(*this->Request->GetContextStack().GetValue()));
            }
            Url += "?" + FString::Join(queryStrings, TEXT("&"));

            request->SetURL(Url);

            request->SetVerb(TEXT("DELETE"));

            request->SetHeader("X-GS2-CLIENT-ID", this->Session->Credential()->ClientId());
            request->SetHeader("Authorization", "Bearer " + this->Session->Credential()->ProjectToken());
            request->SetHeader("Content-Type", "application/json");
            if (this->Request->GetDuplicationAvoider().IsSet())
            {
                request->SetHeader("X-GS2-DUPLICATION-AVOIDER", this->Request->GetDuplicationAvoider().GetValue());
            }
            if (this->Request->GetTimeOffsetToken().IsSet())
            {
                request->SetHeader("X-GS2-TIME-OFFSET-TOKEN", this->Request->GetTimeOffsetToken().GetValue());
            }

            request->ProcessRequest();
            UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s] %s"), TEXT("DELETE"), ToCStr(Url));
        }

        if (FPlatformTLS::GetCurrentThreadId() == GGameThreadId)
        {
            FHttpModule::Get().GetHttpManager().Flush(EHttpFlushReason::FullFlush);
        }
        else
        {
            while (Processing)
            {
                FPlatformProcess::Sleep(0.01f);
            }
        }

        if (ResponseCode / 100 == 2)
        {
            UE_LOG(Gs2Log, Verbose, TEXT("[%d] %s"), ResponseCode, ToCStr(ResponseBody));

            TSharedPtr<FJsonObject> JsonRootObject;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseBody);
                FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
            {
                auto Details = TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>();
                *Result = Result::FWithdrawalByUserIdResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }

    void FWithdrawalByUserIdTask::OnError(Core::Model::FGs2ErrorPtr Error)
    {
        if (Error->Count() > 0 && Error->Detail(0)->Code() == "guild.member.master.require") {
            TGs2Future<Result::FWithdrawalByUserIdResult>::OnError(MakeShared<Guild::Error::FGuildMasterRequiredError>(Error));
        }
        else {
            TGs2Future<Result::FWithdrawalByUserIdResult>::OnError(Error);
        }
    }
}