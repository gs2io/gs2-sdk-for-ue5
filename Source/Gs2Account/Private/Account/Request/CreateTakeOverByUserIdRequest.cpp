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

#include "Account/Request/CreateTakeOverByUserIdRequest.h"

namespace Gs2::Account::Request
{
    FCreateTakeOverByUserIdRequest::FCreateTakeOverByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        TypeValue(TOptional<int32>()),
        UserIdentifierValue(TOptional<FString>()),
        PasswordValue(TOptional<FString>())
    {
    }

    FCreateTakeOverByUserIdRequest::FCreateTakeOverByUserIdRequest(
        const FCreateTakeOverByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        TypeValue(From.TypeValue),
        UserIdentifierValue(From.UserIdentifierValue),
        PasswordValue(From.PasswordValue)
    {
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::WithUserIdentifier(
        const TOptional<FString> UserIdentifier
    )
    {
        this->UserIdentifierValue = UserIdentifier;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::WithPassword(
        const TOptional<FString> Password
    )
    {
        this->PasswordValue = Password;
        return SharedThis(this);
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FCreateTakeOverByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateTakeOverByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateTakeOverByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FCreateTakeOverByUserIdRequest::GetType() const
    {
        return TypeValue;
    }

    FString FCreateTakeOverByUserIdRequest::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }

    TOptional<FString> FCreateTakeOverByUserIdRequest::GetUserIdentifier() const
    {
        return UserIdentifierValue;
    }

    TOptional<FString> FCreateTakeOverByUserIdRequest::GetPassword() const
    {
        return PasswordValue;
    }

    TOptional<FString> FCreateTakeOverByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FCreateTakeOverByUserIdRequest> FCreateTakeOverByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateTakeOverByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
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
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FCreateTakeOverByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}