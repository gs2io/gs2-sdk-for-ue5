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

#include "Mission/Task/Rest/CreateMissionTaskModelMasterTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Mission::Task::Rest
{
    FCreateMissionTaskModelMasterTask::FCreateMissionTaskModelMasterTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FCreateMissionTaskModelMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FCreateMissionTaskModelMasterTask::FCreateMissionTaskModelMasterTask(
        const FCreateMissionTaskModelMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FCreateMissionTaskModelMasterTask::Action(
        const TSharedPtr<Result::FCreateMissionTaskModelMasterResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("mission"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/master/group/{missionGroupName}/task");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );
            Url = Url.Replace(
                TEXT("{missionGroupName}"),
                !this->Request->GetMissionGroupName().IsSet() || this->Request->GetMissionGroupName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetMissionGroupName())
            );

            request->SetURL(Url);

            request->SetVerb(TEXT("POST"));

            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (this->Request->GetName().IsSet() && !this->Request->GetName().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("name", this->Request->GetName().GetValue());
            }
            if (this->Request->GetMetadata().IsSet() && !this->Request->GetMetadata().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("metadata", this->Request->GetMetadata().GetValue());
            }
            if (this->Request->GetDescription().IsSet() && !this->Request->GetDescription().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("description", this->Request->GetDescription().GetValue());
            }
            if (this->Request->GetCounterName().IsSet() && !this->Request->GetCounterName().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("counterName", this->Request->GetCounterName().GetValue());
            }
            if (this->Request->GetTargetResetType().IsSet() && !this->Request->GetTargetResetType().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("targetResetType", this->Request->GetTargetResetType().GetValue());
            }
            if (this->Request->GetTargetValue().IsSet())
            {
                JsonRootObject->SetStringField("targetValue", FString::Printf(TEXT("%lld"), this->Request->GetTargetValue().GetValue()));
            }
            if (this->Request->GetCompleteAcquireActions() != nullptr && this->Request->GetCompleteAcquireActions().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetCompleteAcquireActions())
                {
                    v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
                }
                JsonRootObject->SetArrayField("completeAcquireActions", v);
            }
            if (this->Request->GetChallengePeriodEventId().IsSet() && !this->Request->GetChallengePeriodEventId().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("challengePeriodEventId", this->Request->GetChallengePeriodEventId().GetValue());
            }
            if (this->Request->GetPremiseMissionTaskName().IsSet() && !this->Request->GetPremiseMissionTaskName().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("premiseMissionTaskName", this->Request->GetPremiseMissionTaskName().GetValue());
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
                *Result = Result::FCreateMissionTaskModelMasterResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}