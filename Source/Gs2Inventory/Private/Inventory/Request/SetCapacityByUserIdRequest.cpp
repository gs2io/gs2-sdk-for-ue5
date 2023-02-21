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

#include "Inventory/Request/SetCapacityByUserIdRequest.h"

namespace Gs2::Inventory::Request
{
    FSetCapacityByUserIdRequest::FSetCapacityByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        NewCapacityValueValue(TOptional<int32>())
    {
    }

    FSetCapacityByUserIdRequest::FSetCapacityByUserIdRequest(
        const FSetCapacityByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        UserIdValue(From.UserIdValue),
        NewCapacityValueValue(From.NewCapacityValueValue)
    {
    }

    TSharedPtr<FSetCapacityByUserIdRequest> FSetCapacityByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetCapacityByUserIdRequest> FSetCapacityByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetCapacityByUserIdRequest> FSetCapacityByUserIdRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FSetCapacityByUserIdRequest> FSetCapacityByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSetCapacityByUserIdRequest> FSetCapacityByUserIdRequest::WithNewCapacityValue(
        const TOptional<int32> NewCapacityValue
    )
    {
        this->NewCapacityValueValue = NewCapacityValue;
        return SharedThis(this);
    }

    TSharedPtr<FSetCapacityByUserIdRequest> FSetCapacityByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetCapacityByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetCapacityByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetCapacityByUserIdRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FSetCapacityByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int32> FSetCapacityByUserIdRequest::GetNewCapacityValue() const
    {
        return NewCapacityValueValue;
    }

    FString FSetCapacityByUserIdRequest::GetNewCapacityValueString() const
    {
        if (!NewCapacityValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), NewCapacityValueValue.GetValue());
    }

    TOptional<FString> FSetCapacityByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetCapacityByUserIdRequest> FSetCapacityByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetCapacityByUserIdRequest>()
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
            ->WithInventoryName(Data->HasField("inventoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("inventoryName", v))
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
            ->WithNewCapacityValue(Data->HasField("newCapacityValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("newCapacityValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetCapacityByUserIdRequest::ToJson() const
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
        if (InventoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("inventoryName", InventoryNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (NewCapacityValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("newCapacityValue", NewCapacityValueValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}