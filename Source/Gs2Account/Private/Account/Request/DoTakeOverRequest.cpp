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

#include "Account/Request/DoTakeOverRequest.h"

namespace Gs2::Account::Request
{
    FDoTakeOverRequest::FDoTakeOverRequest():
        NamespaceNameValue(TOptional<FString>()),
        TypeValue(TOptional<int32>()),
        UserIdentifierValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>())
    {
    }

    FDoTakeOverRequest::FDoTakeOverRequest(
        const FDoTakeOverRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        TypeValue(From.TypeValue),
        UserIdentifierValue(From.UserIdentifierValue),
        PasswordValue(From.PasswordValue)
    {
    }

    TSharedPtr<FDoTakeOverRequest> FDoTakeOverRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDoTakeOverRequest> FDoTakeOverRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDoTakeOverRequest> FDoTakeOverRequest::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FDoTakeOverRequest> FDoTakeOverRequest::WithUserIdentifier(
        const TOptional<FString> UserIdentifier
    )
    {
        this->UserIdentifierValue = UserIdentifier;
        return SharedThis(this);
    }

    TSharedPtr<FDoTakeOverRequest> FDoTakeOverRequest::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TOptional<FString> FDoTakeOverRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDoTakeOverRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int32> FDoTakeOverRequest::GetType() const
    {
        return TypeValue;
    }

    FString FDoTakeOverRequest::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), TypeValue.GetValue());
    }

    TOptional<FString> FDoTakeOverRequest::GetUserIdentifier() const
    {
        return UserIdentifierValue;
    }

    TOptional<FString> FDoTakeOverRequest::GetPassword() const
    {
        return PasswordValue;
    }

    TSharedPtr<FDoTakeOverRequest> FDoTakeOverRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDoTakeOverRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("type", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithUserIdentifier(Data->HasField("userIdentifier") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userIdentifier", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithPassword(Data->HasField("password") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("password", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDoTakeOverRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetNumberField("type", TypeValue.GetValue());
        }
        if (UserIdentifierValue.IsSet())
        {
            JsonRootObject->SetStringField("userIdentifier", UserIdentifierValue.GetValue());
        }
        if (PasswordValue.IsSet())
        {
            JsonRootObject->SetStringField("password", PasswordValue.GetValue());
        }
        return JsonRootObject;
    }
}