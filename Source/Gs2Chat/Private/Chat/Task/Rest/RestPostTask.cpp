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

#include "Chat/Task/Rest/PostTask.h"

#include "HttpManager.h"
#include "HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/Rest/Gs2RestSession.h"
#include "Chat/Error/NoAccessPrivilegesError.h"
#include "Chat/Error/PasswordRequiredError.h"
#include "Chat/Error/PasswordIncorrectError.h"
#include "Interfaces/IHttpResponse.h"

namespace Gs2::Chat::Task::Rest
{
    FPostTask::FPostTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FPostRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FPostTask::FPostTask(
        const FPostTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FPostTask::Action(
        const TSharedPtr<Result::FPostResultPtr> Result
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
                .Replace(TEXT("{service}"), TEXT("chat"))
                .Replace(TEXT("{region}"), *this->Session->RegionName())
                .Append("/{namespaceName}/room/{roomName}/message");

            Url = Url.Replace(
                TEXT("{namespaceName}"),
                !this->Request->GetNamespaceName().IsSet() || this->Request->GetNamespaceName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetNamespaceName())
            );
            Url = Url.Replace(
                TEXT("{roomName}"),
                !this->Request->GetRoomName().IsSet() || this->Request->GetRoomName().GetValue().Len() == 0 ?
                    TEXT("null") : ToCStr(*this->Request->GetRoomName())
            );

            request->SetURL(Url);

            request->SetVerb(TEXT("POST"));

            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (this->Request->GetCategory().IsSet())
            {
                JsonRootObject->SetNumberField("category", this->Request->GetCategory().GetValue());
            }
            if (this->Request->GetMetadata().IsSet() && !this->Request->GetMetadata().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("metadata", this->Request->GetMetadata().GetValue());
            }
            if (this->Request->GetPassword().IsSet() && !this->Request->GetPassword().GetValue().IsEmpty())
            {
                JsonRootObject->SetStringField("password", this->Request->GetPassword().GetValue());
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
                *Result = Result::FPostResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }

    void FPostTask::OnError(Core::Model::FGs2ErrorPtr Error)
    {
        if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.allowUserIds.notInclude") {
            TGs2Future<Result::FPostResult>::OnError(MakeShared<Chat::Error::FNoAccessPrivilegesError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.password.require") {
            TGs2Future<Result::FPostResult>::OnError(MakeShared<Chat::Error::FPasswordRequiredError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.password.invalid") {
            TGs2Future<Result::FPostResult>::OnError(MakeShared<Chat::Error::FPasswordIncorrectError>(Error));
        }
        else {
            TGs2Future<Result::FPostResult>::OnError(Error);
        }
    }
}