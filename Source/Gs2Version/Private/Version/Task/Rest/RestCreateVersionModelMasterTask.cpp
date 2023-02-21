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

#include "Version/Task/Rest/CreateVersionModelMasterTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Version::Task::Rest
{
    FCreateVersionModelMasterTask::FCreateVersionModelMasterTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FCreateVersionModelMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FCreateVersionModelMasterTask::FCreateVersionModelMasterTask(
        const FCreateVersionModelMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FCreateVersionModelMasterTask::Action(
        const TSharedPtr<Result::FCreateVersionModelMasterResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("version"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/master/version");

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
            if (this->Request->GetWarningVersion() != nullptr && this->Request->GetWarningVersion().IsValid())
            {
                JsonRootObject->SetObjectField("warningVersion", this->Request->GetWarningVersion()->ToJson());
            }
            if (this->Request->GetErrorVersion() != nullptr && this->Request->GetErrorVersion().IsValid())
            {
                JsonRootObject->SetObjectField("errorVersion", this->Request->GetErrorVersion()->ToJson());
            }
            if (this->Request->GetScope().IsSet())
            {
                JsonRootObject->SetStringField("scope", this->Request->GetScope().GetValue());
            }
            if (this->Request->GetCurrentVersion() != nullptr && this->Request->GetCurrentVersion().IsValid())
            {
                JsonRootObject->SetObjectField("currentVersion", this->Request->GetCurrentVersion()->ToJson());
            }
            if (this->Request->GetNeedSignature().IsSet())
            {
                JsonRootObject->SetBoolField("needSignature", this->Request->GetNeedSignature().GetValue());
            }
            if (this->Request->GetSignatureKeyId().IsSet())
            {
                JsonRootObject->SetStringField("signatureKeyId", this->Request->GetSignatureKeyId().GetValue());
            }
            FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
            request->SetContentAsString(Body);

            request->SetHeader("X-GS2-CLIENT-ID", this->Session->Credential()->ClientId());
            request->SetHeader("Authorization", "Bearer " + this->Session->Credential()->ProjectToken());
            request->SetHeader("Content-Type", "application/json");

            request->ProcessRequest();
            UE_LOG(Gs2Log, Log, TEXT("[%s] %s %s"), TEXT("POST"), ToCStr(Url), ToCStr(Body));
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
                *Result = Result::FCreateVersionModelMasterResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}