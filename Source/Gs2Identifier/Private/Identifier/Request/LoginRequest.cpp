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
 *
 * deny overwrite
 */

#include "Identifier/Request/LoginRequest.h"

namespace Gs2::Identifier::Request
{
    FLoginRequest::FLoginRequest():
        ClientIdValue(TOptional<FString>()),
        ClientSecretValue(TOptional<FString>())
    {
    }

    FLoginRequest::FLoginRequest(
        const FLoginRequest& From
    ):
        ClientIdValue(From.ClientIdValue),
        ClientSecretValue(From.ClientSecretValue)
    {
    }

    TSharedPtr<FLoginRequest> FLoginRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FLoginRequest> FLoginRequest::WithClientId(
        const TOptional<FString> ClientId
    )
    {
        this->ClientIdValue = ClientId;
        return SharedThis(this);
    }

    TSharedPtr<FLoginRequest> FLoginRequest::WithClientSecret(
        const TOptional<FString> ClientSecret
    )
    {
        this->ClientSecretValue = ClientSecret;
        return SharedThis(this);
    }

    TOptional<FString> FLoginRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FLoginRequest::GetClientId() const
    {
        return ClientIdValue;
    }

    TOptional<FString> FLoginRequest::GetClientSecret() const
    {
        return ClientSecretValue;
    }

    TSharedPtr<FLoginRequest> FLoginRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return (new FLoginRequest())
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithClientId(Data->HasField(ANSI_TO_TCHAR("client_id")) ? [Data]() -> TOptional<FString>
              {
                  FString v;
                  if (Data->TryGetStringField(ANSI_TO_TCHAR("client_id"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithClientSecret(Data->HasField(ANSI_TO_TCHAR("client_secret")) ? [Data]() -> TOptional<FString>
              {
                  FString v;
                  if (Data->TryGetStringField(ANSI_TO_TCHAR("client_secret"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FLoginRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (ClientIdValue.IsSet())
        {
            JsonRootObject->SetStringField("client_id", ClientIdValue.GetValue());
        }
        if (ClientSecretValue.IsSet())
        {
            JsonRootObject->SetStringField("client_secret", ClientSecretValue.GetValue());
        }
        return JsonRootObject;
    }
}