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

#include "Ranking/Task/Rest/UpdateCategoryModelMasterTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Ranking::Task::Rest
{
    FUpdateCategoryModelMasterTask::FUpdateCategoryModelMasterTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FUpdateCategoryModelMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FUpdateCategoryModelMasterTask::FUpdateCategoryModelMasterTask(
        const FUpdateCategoryModelMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FUpdateCategoryModelMasterTask::Action(
        const TSharedPtr<Result::FUpdateCategoryModelMasterResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("ranking"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/master/category/{categoryName}");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );
            Url = Url.Replace(
                TEXT("{categoryName}"),
                !this->Request->GetCategoryName().IsSet() || this->Request->GetCategoryName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetCategoryName())
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
            if (this->Request->GetMinimumValue().IsSet())
            {
                JsonRootObject->SetStringField("minimumValue", FString::Printf(TEXT("%lld"), this->Request->GetMinimumValue().GetValue()));
            }
            if (this->Request->GetMaximumValue().IsSet())
            {
                JsonRootObject->SetStringField("maximumValue", FString::Printf(TEXT("%lld"), this->Request->GetMaximumValue().GetValue()));
            }
            if (this->Request->GetOrderDirection().IsSet())
            {
                JsonRootObject->SetStringField("orderDirection", this->Request->GetOrderDirection().GetValue());
            }
            if (this->Request->GetScope().IsSet())
            {
                JsonRootObject->SetStringField("scope", this->Request->GetScope().GetValue());
            }
            if (this->Request->GetGlobalRankingSetting() != nullptr && this->Request->GetGlobalRankingSetting().IsValid())
            {
                JsonRootObject->SetObjectField("globalRankingSetting", this->Request->GetGlobalRankingSetting()->ToJson());
            }
            if (this->Request->GetEntryPeriodEventId().IsSet())
            {
                JsonRootObject->SetStringField("entryPeriodEventId", this->Request->GetEntryPeriodEventId().GetValue());
            }
            if (this->Request->GetAccessPeriodEventId().IsSet())
            {
                JsonRootObject->SetStringField("accessPeriodEventId", this->Request->GetAccessPeriodEventId().GetValue());
            }
            if (this->Request->GetUniqueByUserId().IsSet())
            {
                JsonRootObject->SetBoolField("uniqueByUserId", this->Request->GetUniqueByUserId().GetValue());
            }
            if (this->Request->GetSum().IsSet())
            {
                JsonRootObject->SetBoolField("sum", this->Request->GetSum().GetValue());
            }
            if (this->Request->GetCalculateFixedTimingHour().IsSet())
            {
                JsonRootObject->SetNumberField("calculateFixedTimingHour", this->Request->GetCalculateFixedTimingHour().GetValue());
            }
            if (this->Request->GetCalculateFixedTimingMinute().IsSet())
            {
                JsonRootObject->SetNumberField("calculateFixedTimingMinute", this->Request->GetCalculateFixedTimingMinute().GetValue());
            }
            if (this->Request->GetCalculateIntervalMinutes().IsSet())
            {
                JsonRootObject->SetNumberField("calculateIntervalMinutes", this->Request->GetCalculateIntervalMinutes().GetValue());
            }
            if (this->Request->GetAdditionalScopes() != nullptr && this->Request->GetAdditionalScopes().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetAdditionalScopes())
                {
                    v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
                }
                JsonRootObject->SetArrayField("additionalScopes", v);
            }
            if (this->Request->GetIgnoreUserIds() != nullptr && this->Request->GetIgnoreUserIds().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetIgnoreUserIds())
                {
                    v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
                }
                JsonRootObject->SetArrayField("ignoreUserIds", v);
            }
            if (this->Request->GetGeneration().IsSet())
            {
                JsonRootObject->SetStringField("generation", this->Request->GetGeneration().GetValue());
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
                *Result = Result::FUpdateCategoryModelMasterResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}