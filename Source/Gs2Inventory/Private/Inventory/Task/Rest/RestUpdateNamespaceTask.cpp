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

#include "Inventory/Task/Rest/UpdateNamespaceTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Inventory::Task::Rest
{
    FUpdateNamespaceTask::FUpdateNamespaceTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FUpdateNamespaceTask::FUpdateNamespaceTask(
        const FUpdateNamespaceTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FUpdateNamespaceTask::Action(
        const TSharedPtr<Result::FUpdateNamespaceResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("inventory"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );

            request->SetURL(Url);

            request->SetVerb(TEXT("PUT"));

            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (this->Request->GetDescription().IsSet())
            {
                JsonRootObject->SetStringField("description", this->Request->GetDescription().GetValue());
            }
            if (this->Request->GetAcquireScript() != nullptr && this->Request->GetAcquireScript().IsValid())
            {
                JsonRootObject->SetObjectField("acquireScript", this->Request->GetAcquireScript()->ToJson());
            }
            if (this->Request->GetOverflowScript() != nullptr && this->Request->GetOverflowScript().IsValid())
            {
                JsonRootObject->SetObjectField("overflowScript", this->Request->GetOverflowScript()->ToJson());
            }
            if (this->Request->GetConsumeScript() != nullptr && this->Request->GetConsumeScript().IsValid())
            {
                JsonRootObject->SetObjectField("consumeScript", this->Request->GetConsumeScript()->ToJson());
            }
            if (this->Request->GetSimpleItemAcquireScript() != nullptr && this->Request->GetSimpleItemAcquireScript().IsValid())
            {
                JsonRootObject->SetObjectField("simpleItemAcquireScript", this->Request->GetSimpleItemAcquireScript()->ToJson());
            }
            if (this->Request->GetSimpleItemConsumeScript() != nullptr && this->Request->GetSimpleItemConsumeScript().IsValid())
            {
                JsonRootObject->SetObjectField("simpleItemConsumeScript", this->Request->GetSimpleItemConsumeScript()->ToJson());
            }
            if (this->Request->GetBigItemAcquireScript() != nullptr && this->Request->GetBigItemAcquireScript().IsValid())
            {
                JsonRootObject->SetObjectField("bigItemAcquireScript", this->Request->GetBigItemAcquireScript()->ToJson());
            }
            if (this->Request->GetBigItemConsumeScript() != nullptr && this->Request->GetBigItemConsumeScript().IsValid())
            {
                JsonRootObject->SetObjectField("bigItemConsumeScript", this->Request->GetBigItemConsumeScript()->ToJson());
            }
            if (this->Request->GetLogSetting() != nullptr && this->Request->GetLogSetting().IsValid())
            {
                JsonRootObject->SetObjectField("logSetting", this->Request->GetLogSetting()->ToJson());
            }
            FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
            request->SetContentAsString(Body);

            request->SetHeader("X-GS2-CLIENT-ID", this->Session->Credential()->ClientId());
            request->SetHeader("Authorization", "Bearer " + this->Session->Credential()->ProjectToken());
            request->SetHeader("Content-Type", "application/json");

            request->ProcessRequest();
            UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s] %s %s"), TEXT("PUT"), ToCStr(Url), ToCStr(Body));
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
                *Result = Result::FUpdateNamespaceResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}