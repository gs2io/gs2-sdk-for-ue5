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

#include "Exchange/Task/Rest/UpdateIncrementalRateModelMasterTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Exchange::Task::Rest
{
    FUpdateIncrementalRateModelMasterTask::FUpdateIncrementalRateModelMasterTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FUpdateIncrementalRateModelMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FUpdateIncrementalRateModelMasterTask::FUpdateIncrementalRateModelMasterTask(
        const FUpdateIncrementalRateModelMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FUpdateIncrementalRateModelMasterTask::Action(
        const TSharedPtr<Result::FUpdateIncrementalRateModelMasterResultPtr> Result
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
                .Append("/{namespaceName}/incremental/master/model/{rateName}");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );
            Url = Url.Replace(
                TEXT("{rateName}"),
                !this->Request->GetRateName().IsSet() || this->Request->GetRateName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetRateName())
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
            if (this->Request->GetMetadata().IsSet())
            {
                JsonRootObject->SetStringField("metadata", this->Request->GetMetadata().GetValue());
            }
            if (this->Request->GetConsumeAction() != nullptr && this->Request->GetConsumeAction().IsValid())
            {
                JsonRootObject->SetObjectField("consumeAction", this->Request->GetConsumeAction()->ToJson());
            }
            if (this->Request->GetCalculateType().IsSet())
            {
                JsonRootObject->SetStringField("calculateType", this->Request->GetCalculateType().GetValue());
            }
            if (this->Request->GetBaseValue().IsSet())
            {
                JsonRootObject->SetStringField("baseValue", FString::Printf(TEXT("%lld"), this->Request->GetBaseValue().GetValue()));
            }
            if (this->Request->GetCoefficientValue().IsSet())
            {
                JsonRootObject->SetStringField("coefficientValue", FString::Printf(TEXT("%lld"), this->Request->GetCoefficientValue().GetValue()));
            }
            if (this->Request->GetCalculateScriptId().IsSet())
            {
                JsonRootObject->SetStringField("calculateScriptId", this->Request->GetCalculateScriptId().GetValue());
            }
            if (this->Request->GetExchangeCountId().IsSet())
            {
                JsonRootObject->SetStringField("exchangeCountId", this->Request->GetExchangeCountId().GetValue());
            }
            if (this->Request->GetMaximumExchangeCount().IsSet())
            {
                JsonRootObject->SetNumberField("maximumExchangeCount", this->Request->GetMaximumExchangeCount().GetValue());
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
                *Result = Result::FUpdateIncrementalRateModelMasterResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}