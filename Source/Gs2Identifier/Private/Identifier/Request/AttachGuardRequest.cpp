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

#include "Identifier/Request/AttachGuardRequest.h"

namespace Gs2::Identifier::Request
{
    FAttachGuardRequest::FAttachGuardRequest():
        UserNameValue(TOptional<FString>()),
        ClientIdValue(TOptional<FString>()),
        GuardNamespaceIdValue(TOptional<FString>())
    {
    }

    FAttachGuardRequest::FAttachGuardRequest(
        const FAttachGuardRequest& From
    ):
        UserNameValue(From.UserNameValue),
        ClientIdValue(From.ClientIdValue),
        GuardNamespaceIdValue(From.GuardNamespaceIdValue)
    {
    }

    TSharedPtr<FAttachGuardRequest> FAttachGuardRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FAttachGuardRequest> FAttachGuardRequest::WithUserName(
        const TOptional<FString> UserName
    )
    {
        this->UserNameValue = UserName;
        return SharedThis(this);
    }

    TSharedPtr<FAttachGuardRequest> FAttachGuardRequest::WithClientId(
        const TOptional<FString> ClientId
    )
    {
        this->ClientIdValue = ClientId;
        return SharedThis(this);
    }

    TSharedPtr<FAttachGuardRequest> FAttachGuardRequest::WithGuardNamespaceId(
        const TOptional<FString> GuardNamespaceId
    )
    {
        this->GuardNamespaceIdValue = GuardNamespaceId;
        return SharedThis(this);
    }

    TOptional<FString> FAttachGuardRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FAttachGuardRequest::GetUserName() const
    {
        return UserNameValue;
    }

    TOptional<FString> FAttachGuardRequest::GetClientId() const
    {
        return ClientIdValue;
    }

    TOptional<FString> FAttachGuardRequest::GetGuardNamespaceId() const
    {
        return GuardNamespaceIdValue;
    }

    TSharedPtr<FAttachGuardRequest> FAttachGuardRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAttachGuardRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithUserName(Data->HasField(ANSI_TO_TCHAR("userName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithClientId(Data->HasField(ANSI_TO_TCHAR("clientId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("clientId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGuardNamespaceId(Data->HasField(ANSI_TO_TCHAR("guardNamespaceId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guardNamespaceId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAttachGuardRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (UserNameValue.IsSet())
        {
            JsonRootObject->SetStringField("userName", UserNameValue.GetValue());
        }
        if (ClientIdValue.IsSet())
        {
            JsonRootObject->SetStringField("clientId", ClientIdValue.GetValue());
        }
        if (GuardNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("guardNamespaceId", GuardNamespaceIdValue.GetValue());
        }
        return JsonRootObject;
    }
}