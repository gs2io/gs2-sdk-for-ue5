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

#include "Stamina/Task/Rest/UpdateStaminaModelMasterTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Stamina::Task::Rest
{
    FUpdateStaminaModelMasterTask::FUpdateStaminaModelMasterTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FUpdateStaminaModelMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FUpdateStaminaModelMasterTask::FUpdateStaminaModelMasterTask(
        const FUpdateStaminaModelMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FUpdateStaminaModelMasterTask::Action(
        const TSharedPtr<Result::FUpdateStaminaModelMasterResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("stamina"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/master/model/{staminaName}");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );
            Url = Url.Replace(
                TEXT("{staminaName}"),
                !this->Request->GetStaminaName().IsSet() || this->Request->GetStaminaName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetStaminaName())
            );

            request->SetURL(Url);

            request->SetVerb(TEXT("PUT"));

            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (this->Request->GetDescription().IsSet() && !this->Request->GetDescription().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("description", this->Request->GetDescription().GetValue());
            }
            if (this->Request->GetMetadata().IsSet() && !this->Request->GetMetadata().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("metadata", this->Request->GetMetadata().GetValue());
            }
            if (this->Request->GetRecoverIntervalMinutes().IsSet())
            {
                JsonRootObject->SetNumberField("recoverIntervalMinutes", this->Request->GetRecoverIntervalMinutes().GetValue());
            }
            if (this->Request->GetRecoverValue().IsSet())
            {
                JsonRootObject->SetNumberField("recoverValue", this->Request->GetRecoverValue().GetValue());
            }
            if (this->Request->GetInitialCapacity().IsSet())
            {
                JsonRootObject->SetNumberField("initialCapacity", this->Request->GetInitialCapacity().GetValue());
            }
            if (this->Request->GetIsOverflow().IsSet())
            {
                JsonRootObject->SetBoolField("isOverflow", this->Request->GetIsOverflow().GetValue());
            }
            if (this->Request->GetMaxCapacity().IsSet())
            {
                JsonRootObject->SetNumberField("maxCapacity", this->Request->GetMaxCapacity().GetValue());
            }
            if (this->Request->GetMaxStaminaTableName().IsSet() && !this->Request->GetMaxStaminaTableName().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("maxStaminaTableName", this->Request->GetMaxStaminaTableName().GetValue());
            }
            if (this->Request->GetRecoverIntervalTableName().IsSet() && !this->Request->GetRecoverIntervalTableName().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("recoverIntervalTableName", this->Request->GetRecoverIntervalTableName().GetValue());
            }
            if (this->Request->GetRecoverValueTableName().IsSet() && !this->Request->GetRecoverValueTableName().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("recoverValueTableName", this->Request->GetRecoverValueTableName().GetValue());
            }
            FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
            request->SetContentAsString(Body);

            request->SetHeader("X-GS2-CLIENT-ID", this->Session->Credential()->ClientId());
            request->SetHeader("Authorization", "Bearer " + this->Session->Credential()->ProjectToken());
            request->SetHeader("Content-Type", "application/json");

            request->ProcessRequest();
            UE_LOG(Gs2Log, Log, TEXT("[%s] %s %s"), TEXT("PUT"), ToCStr(Url), ToCStr(Body));
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
            UE_LOG(Gs2Log, Log, TEXT("[%d] %s"), ResponseCode, ToCStr(ResponseBody));

            TSharedPtr<FJsonObject> JsonRootObject;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseBody);
                FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
            {
                auto Details = TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>();
                *Result = Result::FUpdateStaminaModelMasterResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}