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

#include "Exchange/Task/Rest/CreateRateModelMasterTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Exchange::Task::Rest
{
    FCreateRateModelMasterTask::FCreateRateModelMasterTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FCreateRateModelMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FCreateRateModelMasterTask::FCreateRateModelMasterTask(
        const FCreateRateModelMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FCreateRateModelMasterTask::Action(
        const TSharedPtr<Result::FCreateRateModelMasterResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("exchange"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/master/model");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );

            request->SetURL(Url);

            request->SetVerb(TEXT("POST"));

            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (this->Request->GetName().IsSet())
            {
                JsonRootObject->SetStringField("name", this->Request->GetName().GetValue());
            }
            if (this->Request->GetDescription().IsSet())
            {
                JsonRootObject->SetStringField("description", this->Request->GetDescription().GetValue());
            }
            if (this->Request->GetMetadata().IsSet())
            {
                JsonRootObject->SetStringField("metadata", this->Request->GetMetadata().GetValue());
            }
            if (this->Request->GetTimingType().IsSet())
            {
                JsonRootObject->SetStringField("timingType", this->Request->GetTimingType().GetValue());
            }
            if (this->Request->GetLockTime().IsSet())
            {
                JsonRootObject->SetNumberField("lockTime", this->Request->GetLockTime().GetValue());
            }
            if (this->Request->GetAcquireActions() != nullptr && this->Request->GetAcquireActions().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetAcquireActions())
                {
                    v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
                }
                JsonRootObject->SetArrayField("acquireActions", v);
            }
            if (this->Request->GetVerifyActions() != nullptr && this->Request->GetVerifyActions().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetVerifyActions())
                {
                    v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
                }
                JsonRootObject->SetArrayField("verifyActions", v);
            }
            if (this->Request->GetConsumeActions() != nullptr && this->Request->GetConsumeActions().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetConsumeActions())
                {
                    v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
                }
                JsonRootObject->SetArrayField("consumeActions", v);
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
                *Result = Result::FCreateRateModelMasterResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}