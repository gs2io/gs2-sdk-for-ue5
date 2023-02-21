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

#include "Inventory/Request/ConsumeItemSetByUserIdRequest.h"

namespace Gs2::Inventory::Request
{
    FConsumeItemSetByUserIdRequest::FConsumeItemSetByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ItemNameValue(TOptional<FString>()),
        ConsumeCountValue(TOptional<int64>()),
        ItemSetNameValue(TOptional<FString>())
    {
    }

    FConsumeItemSetByUserIdRequest::FConsumeItemSetByUserIdRequest(
        const FConsumeItemSetByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        UserIdValue(From.UserIdValue),
        ItemNameValue(From.ItemNameValue),
        ConsumeCountValue(From.ConsumeCountValue),
        ItemSetNameValue(From.ItemSetNameValue)
    {
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithConsumeCount(
        const TOptional<int64> ConsumeCount
    )
    {
        this->ConsumeCountValue = ConsumeCount;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithItemSetName(
        const TOptional<FString> ItemSetName
    )
    {
        this->ItemSetNameValue = ItemSetName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FConsumeItemSetByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FConsumeItemSetByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FConsumeItemSetByUserIdRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FConsumeItemSetByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FConsumeItemSetByUserIdRequest::GetItemName() const
    {
        return ItemNameValue;
    }

    TOptional<int64> FConsumeItemSetByUserIdRequest::GetConsumeCount() const
    {
        return ConsumeCountValue;
    }

    FString FConsumeItemSetByUserIdRequest::GetConsumeCountString() const
    {
        if (!ConsumeCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ConsumeCountValue.GetValue());
    }

    TOptional<FString> FConsumeItemSetByUserIdRequest::GetItemSetName() const
    {
        return ItemSetNameValue;
    }

    TOptional<FString> FConsumeItemSetByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FConsumeItemSetByUserIdRequest> FConsumeItemSetByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FConsumeItemSetByUserIdRequest>()
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
            ->WithItemName(Data->HasField("itemName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("itemName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithConsumeCount(Data->HasField("consumeCount") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("consumeCount", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithItemSetName(Data->HasField("itemSetName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("itemSetName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FConsumeItemSetByUserIdRequest::ToJson() const
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
        if (ItemNameValue.IsSet())
        {
            JsonRootObject->SetStringField("itemName", ItemNameValue.GetValue());
        }
        if (ConsumeCountValue.IsSet())
        {
            JsonRootObject->SetStringField("consumeCount", FString::Printf(TEXT("%lld"), ConsumeCountValue.GetValue()));
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