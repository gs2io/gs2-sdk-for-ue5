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

#include "Guild/Task/Rest/UpdateNamespaceTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Guild::Task::Rest
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
                .Replace(TEXT("{service}"), TEXT("guild"))
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
            if (this->Request->GetChangeNotification() != nullptr && this->Request->GetChangeNotification().IsValid())
            {
                JsonRootObject->SetObjectField("changeNotification", this->Request->GetChangeNotification()->ToJson());
            }
            if (this->Request->GetJoinNotification() != nullptr && this->Request->GetJoinNotification().IsValid())
            {
                JsonRootObject->SetObjectField("joinNotification", this->Request->GetJoinNotification()->ToJson());
            }
            if (this->Request->GetLeaveNotification() != nullptr && this->Request->GetLeaveNotification().IsValid())
            {
                JsonRootObject->SetObjectField("leaveNotification", this->Request->GetLeaveNotification()->ToJson());
            }
            if (this->Request->GetChangeMemberNotification() != nullptr && this->Request->GetChangeMemberNotification().IsValid())
            {
                JsonRootObject->SetObjectField("changeMemberNotification", this->Request->GetChangeMemberNotification()->ToJson());
            }
            if (this->Request->GetReceiveRequestNotification() != nullptr && this->Request->GetReceiveRequestNotification().IsValid())
            {
                JsonRootObject->SetObjectField("receiveRequestNotification", this->Request->GetReceiveRequestNotification()->ToJson());
            }
            if (this->Request->GetRemoveRequestNotification() != nullptr && this->Request->GetRemoveRequestNotification().IsValid())
            {
                JsonRootObject->SetObjectField("removeRequestNotification", this->Request->GetRemoveRequestNotification()->ToJson());
            }
            if (this->Request->GetCreateGuildScript() != nullptr && this->Request->GetCreateGuildScript().IsValid())
            {
                JsonRootObject->SetObjectField("createGuildScript", this->Request->GetCreateGuildScript()->ToJson());
            }
            if (this->Request->GetUpdateGuildScript() != nullptr && this->Request->GetUpdateGuildScript().IsValid())
            {
                JsonRootObject->SetObjectField("updateGuildScript", this->Request->GetUpdateGuildScript()->ToJson());
            }
            if (this->Request->GetJoinGuildScript() != nullptr && this->Request->GetJoinGuildScript().IsValid())
            {
                JsonRootObject->SetObjectField("joinGuildScript", this->Request->GetJoinGuildScript()->ToJson());
            }
            if (this->Request->GetReceiveJoinRequestScript() != nullptr && this->Request->GetReceiveJoinRequestScript().IsValid())
            {
                JsonRootObject->SetObjectField("receiveJoinRequestScript", this->Request->GetReceiveJoinRequestScript()->ToJson());
            }
            if (this->Request->GetLeaveGuildScript() != nullptr && this->Request->GetLeaveGuildScript().IsValid())
            {
                JsonRootObject->SetObjectField("leaveGuildScript", this->Request->GetLeaveGuildScript()->ToJson());
            }
            if (this->Request->GetChangeRoleScript() != nullptr && this->Request->GetChangeRoleScript().IsValid())
            {
                JsonRootObject->SetObjectField("changeRoleScript", this->Request->GetChangeRoleScript()->ToJson());
            }
            if (this->Request->GetDeleteGuildScript() != nullptr && this->Request->GetDeleteGuildScript().IsValid())
            {
                JsonRootObject->SetObjectField("deleteGuildScript", this->Request->GetDeleteGuildScript()->ToJson());
            }
            if (this->Request->GetLogSetting() != nullptr && this->Request->GetLogSetting().IsValid())
            {
                JsonRootObject->SetObjectField("logSetting", this->Request->GetLogSetting()->ToJson());
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