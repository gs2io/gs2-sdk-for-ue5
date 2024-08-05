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

#include "Log/Task/Rest/UpdateNamespaceTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Log::Task::Rest
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
                .Replace(TEXT("{service}"), TEXT("log"))
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
            if (this->Request->GetType().IsSet())
            {
                JsonRootObject->SetStringField("type", this->Request->GetType().GetValue());
            }
            if (this->Request->GetGcpCredentialJson().IsSet())
            {
                JsonRootObject->SetStringField("gcpCredentialJson", this->Request->GetGcpCredentialJson().GetValue());
            }
            if (this->Request->GetBigQueryDatasetName().IsSet())
            {
                JsonRootObject->SetStringField("bigQueryDatasetName", this->Request->GetBigQueryDatasetName().GetValue());
            }
            if (this->Request->GetLogExpireDays().IsSet())
            {
                JsonRootObject->SetNumberField("logExpireDays", this->Request->GetLogExpireDays().GetValue());
            }
            if (this->Request->GetAwsRegion().IsSet())
            {
                JsonRootObject->SetStringField("awsRegion", this->Request->GetAwsRegion().GetValue());
            }
            if (this->Request->GetAwsAccessKeyId().IsSet())
            {
                JsonRootObject->SetStringField("awsAccessKeyId", this->Request->GetAwsAccessKeyId().GetValue());
            }
            if (this->Request->GetAwsSecretAccessKey().IsSet())
            {
                JsonRootObject->SetStringField("awsSecretAccessKey", this->Request->GetAwsSecretAccessKey().GetValue());
            }
            if (this->Request->GetFirehoseStreamName().IsSet())
            {
                JsonRootObject->SetStringField("firehoseStreamName", this->Request->GetFirehoseStreamName().GetValue());
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