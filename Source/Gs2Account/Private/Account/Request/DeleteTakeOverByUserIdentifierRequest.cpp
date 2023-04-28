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

#include "Account/Request/DeleteTakeOverByUserIdentifierRequest.h"

namespace Gs2::Account::Request
{
    FDeleteTakeOverByUserIdentifierRequest::FDeleteTakeOverByUserIdentifierRequest():
        NamespaceNameValue(TOptional<FString>()),
        TypeValue(TOptional<int32>()),
        UserIdentifierValue(TOptional<FString>())
    {
    }

    FDeleteTakeOverByUserIdentifierRequest::FDeleteTakeOverByUserIdentifierRequest(
        const FDeleteTakeOverByUserIdentifierRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        TypeValue(From.TypeValue),
        UserIdentifierValue(From.UserIdentifierValue)
    {
    }

    TSharedPtr<FDeleteTakeOverByUserIdentifierRequest> FDeleteTakeOverByUserIdentifierRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteTakeOverByUserIdentifierRequest> FDeleteTakeOverByUserIdentifierRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteTakeOverByUserIdentifierRequest> FDeleteTakeOverByUserIdentifierRequest::WithType(
        const TOptional<int32> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteTakeOverByUserIdentifierRequest> FDeleteTakeOverByUserIdentifierRequest::WithUserIdentifier(
        const TOptional<FString> UserIdentifier
    )
    {
        this->UserIdentifierValue = UserIdentifier;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteTakeOverByUserIdentifierRequest> FDeleteTakeOverByUserIdentifierRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteTakeOverByUserIdentifierRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteTakeOverByUserIdentifierRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<int32> FDeleteTakeOverByUserIdentifierRequest::GetType() const
    {
        return TypeValue;
    }

    FString FDeleteTakeOverByUserIdentifierRequest::GetTypeString() const
    {
        if (!TypeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), TypeValue.GetValue());
    }

    TOptional<FString> FDeleteTakeOverByUserIdentifierRequest::GetUserIdentifier() const
    {
        return UserIdentifierValue;
    }

    TOptional<FString> FDeleteTakeOverByUserIdentifierRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDeleteTakeOverByUserIdentifierRequest> FDeleteTakeOverByUserIdentifierRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteTakeOverByUserIdentifierRequest>()
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
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteTakeOverByUserIdentifierRequest::ToJson() const
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
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}