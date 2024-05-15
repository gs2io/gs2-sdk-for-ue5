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

#include "Guild/Task/Rest/SearchGuildsTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Guild::Task::Rest
{
    FSearchGuildsTask::FSearchGuildsTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FSearchGuildsRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FSearchGuildsTask::FSearchGuildsTask(
        const FSearchGuildsTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FSearchGuildsTask::Action(
        const TSharedPtr<Result::FSearchGuildsResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("guild"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/user/me/guild/{guildModelName}/search");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );
            Url = Url.Replace(
                TEXT("{guildModelName}"),
                !this->Request->GetGuildModelName().IsSet() || this->Request->GetGuildModelName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetGuildModelName())
            );

            request->SetURL(Url);

            request->SetVerb(TEXT("POST"));

            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (this->Request->GetDisplayName().IsSet())
            {
                JsonRootObject->SetStringField("displayName", this->Request->GetDisplayName().GetValue());
            }
            if (this->Request->GetAttributes1() != nullptr && this->Request->GetAttributes1().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetAttributes1())
                {
                    v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
                }
                JsonRootObject->SetArrayField("attributes1", v);
            }
            if (this->Request->GetAttributes2() != nullptr && this->Request->GetAttributes2().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetAttributes2())
                {
                    v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
                }
                JsonRootObject->SetArrayField("attributes2", v);
            }
            if (this->Request->GetAttributes3() != nullptr && this->Request->GetAttributes3().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetAttributes3())
                {
                    v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
                }
                JsonRootObject->SetArrayField("attributes3", v);
            }
            if (this->Request->GetAttributes4() != nullptr && this->Request->GetAttributes4().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetAttributes4())
                {
                    v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
                }
                JsonRootObject->SetArrayField("attributes4", v);
            }
            if (this->Request->GetAttributes5() != nullptr && this->Request->GetAttributes5().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetAttributes5())
                {
                    v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
                }
                JsonRootObject->SetArrayField("attributes5", v);
            }
            if (this->Request->GetJoinPolicies() != nullptr && this->Request->GetJoinPolicies().IsValid())
            {
                TArray<TSharedPtr<FJsonValue>> v;
                for (auto JsonObjectValue : *this->Request->GetJoinPolicies())
                {
                    v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
                }
                JsonRootObject->SetArrayField("joinPolicies", v);
            }
            if (this->Request->GetIncludeFullMembersGuild().IsSet())
            {
                JsonRootObject->SetBoolField("includeFullMembersGuild", this->Request->GetIncludeFullMembersGuild().GetValue());
            }
            if (this->Request->GetPageToken().IsSet())
            {
                JsonRootObject->SetStringField("pageToken", this->Request->GetPageToken().GetValue());
            }
            if (this->Request->GetLimit().IsSet())
            {
                JsonRootObject->SetNumberField("limit", this->Request->GetLimit().GetValue());
            }
            FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
            request->SetContentAsString(Body);

            request->SetHeader("X-GS2-CLIENT-ID", this->Session->Credential()->ClientId());
            request->SetHeader("Authorization", "Bearer " + this->Session->Credential()->ProjectToken());
            request->SetHeader("Content-Type", "application/json");
            if (this->Request->GetAccessToken().IsSet())
            {
                request->SetHeader("X-GS2-ACCESS-TOKEN", this->Request->GetAccessToken().GetValue());
            }
            if (this->Request->GetDuplicationAvoider().IsSet())
            {
                request->SetHeader("X-GS2-DUPLICATION-AVOIDER", this->Request->GetDuplicationAvoider().GetValue());
            }

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
                *Result = Result::FSearchGuildsResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}