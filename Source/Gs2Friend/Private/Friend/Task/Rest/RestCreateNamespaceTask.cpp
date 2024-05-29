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

#include "Friend/Task/Rest/CreateNamespaceTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Friend::Task::Rest
{
    FCreateNamespaceTask::FCreateNamespaceTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FCreateNamespaceRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FCreateNamespaceTask::Action(
        const TSharedPtr<Result::FCreateNamespaceResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("friend"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/");

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
            if (this->Request->GetFollowScript() != nullptr && this->Request->GetFollowScript().IsValid())
            {
                JsonRootObject->SetObjectField("followScript", this->Request->GetFollowScript()->ToJson());
            }
            if (this->Request->GetUnfollowScript() != nullptr && this->Request->GetUnfollowScript().IsValid())
            {
                JsonRootObject->SetObjectField("unfollowScript", this->Request->GetUnfollowScript()->ToJson());
            }
            if (this->Request->GetSendRequestScript() != nullptr && this->Request->GetSendRequestScript().IsValid())
            {
                JsonRootObject->SetObjectField("sendRequestScript", this->Request->GetSendRequestScript()->ToJson());
            }
            if (this->Request->GetCancelRequestScript() != nullptr && this->Request->GetCancelRequestScript().IsValid())
            {
                JsonRootObject->SetObjectField("cancelRequestScript", this->Request->GetCancelRequestScript()->ToJson());
            }
            if (this->Request->GetAcceptRequestScript() != nullptr && this->Request->GetAcceptRequestScript().IsValid())
            {
                JsonRootObject->SetObjectField("acceptRequestScript", this->Request->GetAcceptRequestScript()->ToJson());
            }
            if (this->Request->GetRejectRequestScript() != nullptr && this->Request->GetRejectRequestScript().IsValid())
            {
                JsonRootObject->SetObjectField("rejectRequestScript", this->Request->GetRejectRequestScript()->ToJson());
            }
            if (this->Request->GetDeleteFriendScript() != nullptr && this->Request->GetDeleteFriendScript().IsValid())
            {
                JsonRootObject->SetObjectField("deleteFriendScript", this->Request->GetDeleteFriendScript()->ToJson());
            }
            if (this->Request->GetUpdateProfileScript() != nullptr && this->Request->GetUpdateProfileScript().IsValid())
            {
                JsonRootObject->SetObjectField("updateProfileScript", this->Request->GetUpdateProfileScript()->ToJson());
            }
            if (this->Request->GetFollowNotification() != nullptr && this->Request->GetFollowNotification().IsValid())
            {
                JsonRootObject->SetObjectField("followNotification", this->Request->GetFollowNotification()->ToJson());
            }
            if (this->Request->GetReceiveRequestNotification() != nullptr && this->Request->GetReceiveRequestNotification().IsValid())
            {
                JsonRootObject->SetObjectField("receiveRequestNotification", this->Request->GetReceiveRequestNotification()->ToJson());
            }
            if (this->Request->GetAcceptRequestNotification() != nullptr && this->Request->GetAcceptRequestNotification().IsValid())
            {
                JsonRootObject->SetObjectField("acceptRequestNotification", this->Request->GetAcceptRequestNotification()->ToJson());
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
                *Result = Result::FCreateNamespaceResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}