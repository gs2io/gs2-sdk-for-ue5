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

#include "Chat/Task/Rest/DescribeLatestMessagesByUserIdTask.h"

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
    FDescribeLatestMessagesByUserIdTask::FDescribeLatestMessagesByUserIdTask(
        const Core::Net::Rest::FGs2RestSessionPtr Session,
        const Request::FDescribeLatestMessagesByUserIdRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FDescribeLatestMessagesByUserIdTask::FDescribeLatestMessagesByUserIdTask(
        const FDescribeLatestMessagesByUserIdTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FDescribeLatestMessagesByUserIdTask::Action(
        const TSharedPtr<Result::FDescribeLatestMessagesByUserIdResultPtr> Result
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
                .Append("/{namespaceName}/room/{roomName}/message/latest/get");

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

            TArray<FString> queryStrings;
            if (this->Request->GetContextStack().IsSet()) {
                queryStrings.Add("contextStack=" + FGenericPlatformHttp::UrlEncode(*this->Request->GetContextStack().GetValue()));
            }
            if (this->Request->GetPassword().IsSet()) {
                queryStrings.Add("password=" + FGenericPlatformHttp::UrlEncode(this->Request->GetPassword().GetValue()));
            }
            if (this->Request->GetCategory().IsSet()) {
                queryStrings.Add("category=" + this->Request->GetCategoryString());
            }
            if (this->Request->GetUserId().IsSet()) {
                queryStrings.Add("userId=" + FGenericPlatformHttp::UrlEncode(this->Request->GetUserId().GetValue()));
            }
            if (this->Request->GetPageToken().IsSet()) {
                queryStrings.Add("pageToken=" + FGenericPlatformHttp::UrlEncode(this->Request->GetPageToken().GetValue()));
            }
            if (this->Request->GetLimit().IsSet()) {
                queryStrings.Add("limit=" + this->Request->GetLimitString());
            }
            Url += "?" + FString::Join(queryStrings, TEXT("&"));

            request->SetURL(Url);

            request->SetVerb(TEXT("GET"));

            request->SetHeader("X-GS2-CLIENT-ID", this->Session->Credential()->ClientId());
            request->SetHeader("Authorization", "Bearer " + this->Session->Credential()->ProjectToken());
            request->SetHeader("Content-Type", "application/json");
            if (this->Request->GetTimeOffsetToken().IsSet())
            {
                request->SetHeader("X-GS2-TIME-OFFSET-TOKEN", this->Request->GetTimeOffsetToken().GetValue());
            }

            request->ProcessRequest();
            UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s] %s"), TEXT("GET"), ToCStr(Url));
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
                *Result = Result::FDescribeLatestMessagesByUserIdResult::FromJson(JsonRootObject);
                return nullptr;
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        return Core::Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }

    void FDescribeLatestMessagesByUserIdTask::OnError(Core::Model::FGs2ErrorPtr Error)
    {
        if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.allowUserIds.notInclude") {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(MakeShared<Chat::Error::FNoAccessPrivilegesError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.password.require") {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(MakeShared<Chat::Error::FPasswordRequiredError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.password.invalid") {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(MakeShared<Chat::Error::FPasswordIncorrectError>(Error));
        }
        else {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(Error);
        }
    }
}