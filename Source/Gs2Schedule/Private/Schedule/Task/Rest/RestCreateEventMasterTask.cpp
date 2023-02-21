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

#include "Schedule/Task/Rest/CreateEventMasterTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Schedule::Task::Rest
{
    FCreateEventMasterTask::FCreateEventMasterTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FCreateEventMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FCreateEventMasterTask::FCreateEventMasterTask(
        const FCreateEventMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FCreateEventMasterTask::Action(
        const TSharedPtr<Result::FCreateEventMasterResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("schedule"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/master/event");

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
            if (this->Request->GetScheduleType().IsSet())
            {
                JsonRootObject->SetStringField("scheduleType", this->Request->GetScheduleType().GetValue());
            }
            if (this->Request->GetAbsoluteBegin().IsSet())
            {
                JsonRootObject->SetStringField("absoluteBegin", FString::Printf(TEXT("%lld"), this->Request->GetAbsoluteBegin().GetValue()));
            }
            if (this->Request->GetAbsoluteEnd().IsSet())
            {
                JsonRootObject->SetStringField("absoluteEnd", FString::Printf(TEXT("%lld"), this->Request->GetAbsoluteEnd().GetValue()));
            }
            if (this->Request->GetRepeatType().IsSet())
            {
                JsonRootObject->SetStringField("repeatType", this->Request->GetRepeatType().GetValue());
            }
            if (this->Request->GetRepeatBeginDayOfMonth().IsSet())
            {
                JsonRootObject->SetNumberField("repeatBeginDayOfMonth", this->Request->GetRepeatBeginDayOfMonth().GetValue());
            }
            if (this->Request->GetRepeatEndDayOfMonth().IsSet())
            {
                JsonRootObject->SetNumberField("repeatEndDayOfMonth", this->Request->GetRepeatEndDayOfMonth().GetValue());
            }
            if (this->Request->GetRepeatBeginDayOfWeek().IsSet())
            {
                JsonRootObject->SetStringField("repeatBeginDayOfWeek", this->Request->GetRepeatBeginDayOfWeek().GetValue());
            }
            if (this->Request->GetRepeatEndDayOfWeek().IsSet())
            {
                JsonRootObject->SetStringField("repeatEndDayOfWeek", this->Request->GetRepeatEndDayOfWeek().GetValue());
            }
            if (this->Request->GetRepeatBeginHour().IsSet())
            {
                JsonRootObject->SetNumberField("repeatBeginHour", this->Request->GetRepeatBeginHour().GetValue());
            }
            if (this->Request->GetRepeatEndHour().IsSet())
            {
                JsonRootObject->SetNumberField("repeatEndHour", this->Request->GetRepeatEndHour().GetValue());
            }
            if (this->Request->GetRelativeTriggerName().IsSet())
            {
                JsonRootObject->SetStringField("relativeTriggerName", this->Request->GetRelativeTriggerName().GetValue());
            }
            if (this->Request->GetRelativeDuration().IsSet())
            {
                JsonRootObject->SetNumberField("relativeDuration", this->Request->GetRelativeDuration().GetValue());
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
                *Result = Result::FCreateEventMasterResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}