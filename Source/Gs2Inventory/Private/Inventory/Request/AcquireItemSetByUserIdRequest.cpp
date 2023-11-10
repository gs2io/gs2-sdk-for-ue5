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

#include "Inventory/Request/AcquireItemSetByUserIdRequest.h"

namespace Gs2::Inventory::Request
{
    FAcquireItemSetByUserIdRequest::FAcquireItemSetByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        ItemNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        AcquireCountValue(TOptional<int64>()),
        ExpiresAtValue(TOptional<int64>()),
        CreateNewItemSetValue(TOptional<bool>()),
        ItemSetNameValue(TOptional<FString>())
    {
    }

    FAcquireItemSetByUserIdRequest::FAcquireItemSetByUserIdRequest(
        const FAcquireItemSetByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        ItemNameValue(From.ItemNameValue),
        UserIdValue(From.UserIdValue),
        AcquireCountValue(From.AcquireCountValue),
        ExpiresAtValue(From.ExpiresAtValue),
        CreateNewItemSetValue(From.CreateNewItemSetValue),
        ItemSetNameValue(From.ItemSetNameValue)
    {
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithAcquireCount(
        const TOptional<int64> AcquireCount
    )
    {
        this->AcquireCountValue = AcquireCount;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithCreateNewItemSet(
        const TOptional<bool> CreateNewItemSet
    )
    {
        this->CreateNewItemSetValue = CreateNewItemSet;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithItemSetName(
        const TOptional<FString> ItemSetName
    )
    {
        this->ItemSetNameValue = ItemSetName;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FAcquireItemSetByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FAcquireItemSetByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FAcquireItemSetByUserIdRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FAcquireItemSetByUserIdRequest::GetItemName() const
    {
        return ItemNameValue;
    }

    TOptional<FString> FAcquireItemSetByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int64> FAcquireItemSetByUserIdRequest::GetAcquireCount() const
    {
        return AcquireCountValue;
    }

    FString FAcquireItemSetByUserIdRequest::GetAcquireCountString() const
    {
        if (!AcquireCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AcquireCountValue.GetValue());
    }

    TOptional<int64> FAcquireItemSetByUserIdRequest::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FAcquireItemSetByUserIdRequest::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    TOptional<bool> FAcquireItemSetByUserIdRequest::GetCreateNewItemSet() const
    {
        return CreateNewItemSetValue;
    }

    FString FAcquireItemSetByUserIdRequest::GetCreateNewItemSetString() const
    {
        if (!CreateNewItemSetValue.IsSet())
        {
            return FString("null");
        }
        return FString(CreateNewItemSetValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FAcquireItemSetByUserIdRequest::GetItemSetName() const
    {
        return ItemSetNameValue;
    }

    TOptional<FString> FAcquireItemSetByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FAcquireItemSetByUserIdRequest> FAcquireItemSetByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireItemSetByUserIdRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithInventoryName(Data->HasField("inventoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("inventoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithItemName(Data->HasField("itemName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("itemName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAcquireCount(Data->HasField("acquireCount") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("acquireCount", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithExpiresAt(Data->HasField("expiresAt") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("expiresAt", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithCreateNewItemSet(Data->HasField("createNewItemSet") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("createNewItemSet", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithItemSetName(Data->HasField("itemSetName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("itemSetName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAcquireItemSetByUserIdRequest::ToJson() const
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
        if (ItemNameValue.IsSet())
        {
            JsonRootObject->SetStringField("itemName", ItemNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (AcquireCountValue.IsSet())
        {
            JsonRootObject->SetStringField("acquireCount", FString::Printf(TEXT("%lld"), AcquireCountValue.GetValue()));
        }
        if (ExpiresAtValue.IsSet())
        {
            JsonRootObject->SetStringField("expiresAt", FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue()));
        }
        if (CreateNewItemSetValue.IsSet())
        {
            JsonRootObject->SetBoolField("createNewItemSet", CreateNewItemSetValue.GetValue());
        }
        if (ItemSetNameValue.IsSet())
        {
            JsonRootObject->SetStringField("itemSetName", ItemSetNameValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}