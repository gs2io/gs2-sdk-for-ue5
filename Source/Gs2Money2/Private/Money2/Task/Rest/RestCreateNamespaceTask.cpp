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

#include "Money2/Task/Rest/CreateNamespaceTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Money2::Task::Rest
{
    FCreateNamespaceTask::FCreateNamespaceTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FCreateNamespaceRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FCreateNamespaceTask::Action(
        const TSharedPtr<Result::FCreateNamespaceResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("money2"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/");

            request->SetURL(Url);

            request->SetVerb(TEXT("POST"));

            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (this->Request->GetName().IsSet())
            {
                JsonRootObject->SetStringField("name", this->Request->GetName().GetValue());
            }
            if (this->Request->GetCurrencyUsagePriority().IsSet())
            {
                JsonRootObject->SetStringField("currencyUsagePriority", this->Request->GetCurrencyUsagePriority().GetValue());
            }
            if (this->Request->GetDescription().IsSet())
            {
                JsonRootObject->SetStringField("description", this->Request->GetDescription().GetValue());
            }
            if (this->Request->GetSharedFreeCurrency().IsSet())
            {
                JsonRootObject->SetBoolField("sharedFreeCurrency", this->Request->GetSharedFreeCurrency().GetValue());
            }
            if (this->Request->GetPlatformSetting() != nullptr && this->Request->GetPlatformSetting().IsValid())
            {
                JsonRootObject->SetObjectField("platformSetting", this->Request->GetPlatformSetting()->ToJson());
            }
            if (this->Request->GetDepositBalanceScript() != nullptr && this->Request->GetDepositBalanceScript().IsValid())
            {
                JsonRootObject->SetObjectField("depositBalanceScript", this->Request->GetDepositBalanceScript()->ToJson());
            }
            if (this->Request->GetWithdrawBalanceScript() != nullptr && this->Request->GetWithdrawBalanceScript().IsValid())
            {
                JsonRootObject->SetObjectField("withdrawBalanceScript", this->Request->GetWithdrawBalanceScript()->ToJson());
            }
            if (this->Request->GetSubscribeScript().IsSet())
            {
                JsonRootObject->SetStringField("subscribeScript", this->Request->GetSubscribeScript().GetValue());
            }
            if (this->Request->GetRenewScript().IsSet())
            {
                JsonRootObject->SetStringField("renewScript", this->Request->GetRenewScript().GetValue());
            }
            if (this->Request->GetUnsubscribeScript().IsSet())
            {
                JsonRootObject->SetStringField("unsubscribeScript", this->Request->GetUnsubscribeScript().GetValue());
            }
            if (this->Request->GetTakeOverScript() != nullptr && this->Request->GetTakeOverScript().IsValid())
            {
                JsonRootObject->SetObjectField("takeOverScript", this->Request->GetTakeOverScript()->ToJson());
            }
            if (this->Request->GetChangeSubscriptionStatusNotification() != nullptr && this->Request->GetChangeSubscriptionStatusNotification().IsValid())
            {
                JsonRootObject->SetObjectField("changeSubscriptionStatusNotification", this->Request->GetChangeSubscriptionStatusNotification()->ToJson());
            }
            if (this->Request->GetLogSetting() != nullptr && this->Request->GetLogSetting().IsValid())
            {
                JsonRootObject->SetObjectField("logSetting", this->Request->GetLogSetting()->ToJson());
            }
            if (this->Request->GetContextStack().IsSet())
            {
                JsonRootObject->SetStringField("contextStack", this->Request->GetContextStack().GetValue());
            }
            FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
            request->SetContentAsString(Body);

            request->SetHeader("X-GS2-CLIENT-ID", this->Session->Credential()->ClientId());
            request->SetHeader("Authorization", "Bearer " + this->Session->Credential()->ProjectToken());
            request->SetHeader("Content-Type", "application/json");

            request->ProcessRequest();
            UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s] %s %s"), TEXT("POST"), ToCStr(Url), ToCStr(Body));
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
                *Result = Result::FCreateNamespaceResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}