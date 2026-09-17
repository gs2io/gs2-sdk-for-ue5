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


#include "Core/Net/Rest/Task/RestOpenTask.h"

#include "Core/Gs2Constant.h"
#include "Core/Model/Gs2Error.h"
#include "Core/Net/Rest/RestSessionRequest.h"

namespace Gs2::Core::Net::Rest::Task
{
    FRestOpenTask::FRestOpenTask(const FGs2RestSessionPtr Session): Session(Session)
    {

    }

    FRestOpenTask::~FRestOpenTask()
    {
    }

    Model::FGs2ErrorPtr FRestOpenTask::Action(TSharedPtr<TSharedPtr<Result::FOpenTaskResult>> Result)
    {
        if (Session->Credential()->IsProjectTokenCredential())
        {
            Session->SetOwnerId(Session->Credential()->ClientId());
            *Result = MakeShared<Result::FOpenTaskResult>();
            return nullptr;
        }
        FString Body;
        {
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (Session->Credential()->ClientId() != "")
            {
                JsonRootObject->SetStringField(TEXT("client_id"), Session->Credential()->ClientId());
            }
            if (Session->Credential()->ClientSecret() != "")
            {
                JsonRootObject->SetStringField(TEXT("client_secret"), Session->Credential()->ClientSecret());
            }
            FJsonSerializer::Serialize(JsonRootObject.ToSharedRef(), Writer);
        }

        // steady 未設定なら従来どおり FGs2Constant::EndpointHost の置換、設定済みなら <steady>/identifier。
        const auto Url = this->Session->EndpointHost(TEXT("identifier"))
                         .Append("/projectToken/login");

        // ★セッションの Send 経路を通す（Steady のときだけ接続段階の失敗で同じ要求を 1 回だけ再送する）。
        FRestSessionRequest Request(TEXT("POST"), Url);
        Request
            .AddHeader("Content-Type", "application/json")
            .SetBody(Body);

        const auto Response = Session->Send(Request);
        if (!Response.HasResponse())
        {
            // 応答が 1 つも得られなかった（接続段階の失敗・タイムアウト・送信後の切断）。
            UE_LOG(Gs2Log, Warning, TEXT("no response from %s"), ToCStr(Url));
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FUnknownError>(Details);
        }
        const auto ResponseCode = Response.ResponseCode;
        const auto ResponseBody = Response.ResponseBody;

        if (ResponseCode == 200)
        {
            UE_LOG(Gs2Log, Verbose, TEXT("[%d] %s"), ResponseCode, ToCStr(ResponseBody));

            TSharedPtr<FJsonObject> JsonRootObject;
            const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseBody);
            const bool bParsed = FJsonSerializer::Deserialize(JsonReader, JsonRootObject);
            if (bParsed && JsonRootObject.IsValid())
            {
                FString Token;
                if (JsonRootObject->TryGetStringField(ANSI_TO_TCHAR("access_token"), Token))
                {
                    FString OwnerId;
                    JsonRootObject->TryGetStringField(ANSI_TO_TCHAR("owner_id"), OwnerId);
                    Session->Credential()->UpdateProjectToken(Token);
                    Session->SetOwnerId(OwnerId);
                    *Result = MakeShared<Result::FOpenTaskResult>();
                    return nullptr;
                }
            }
            const auto Details = MakeShared<TArray<TSharedPtr<Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Model::FGs2ErrorDetail>(
                TEXT("client"),
                bParsed && JsonRootObject.IsValid()
                    ? TEXT("Login response did not contain an access token.")
                    : TEXT("core.network.result.error.parse.failed"),
                TEXT("")
            ));
            return MakeShared<Model::FUnknownError>(Details);
        }
        return Model::FGs2Error::FromResponse(ResponseCode, ResponseBody);
    }
}
