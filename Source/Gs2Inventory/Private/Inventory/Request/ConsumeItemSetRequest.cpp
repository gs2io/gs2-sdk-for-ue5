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

#include "Inventory/Request/ConsumeItemSetRequest.h"

namespace Gs2::Inventory::Request
{
    FConsumeItemSetRequest::FConsumeItemSetRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        ItemNameValue(TOptional<FString>()),
        ConsumeCountValue(TOptional<int64>()),
        ItemSetNameValue(TOptional<FString>())
    {
    }

    FConsumeItemSetRequest::FConsumeItemSetRequest(
        const FConsumeItemSetRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        AccessTokenValue(From.AccessTokenValue),
        ItemNameValue(From.ItemNameValue),
        ConsumeCountValue(From.ConsumeCountValue),
        ItemSetNameValue(From.ItemSetNameValue)
    {
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithConsumeCount(
        const TOptional<int64> ConsumeCount
    )
    {
        this->ConsumeCountValue = ConsumeCount;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithItemSetName(
        const TOptional<FString> ItemSetName
    )
    {
        this->ItemSetNameValue = ItemSetName;
        return SharedThis(this);
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FConsumeItemSetRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FConsumeItemSetRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FConsumeItemSetRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FConsumeItemSetRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FConsumeItemSetRequest::GetItemName() const
    {
        return ItemNameValue;
    }

    TOptional<int64> FConsumeItemSetRequest::GetConsumeCount() const
    {
        return ConsumeCountValue;
    }

    FString FConsumeItemSetRequest::GetConsumeCountString() const
    {
        if (!ConsumeCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ConsumeCountValue.GetValue());
    }

    TOptional<FString> FConsumeItemSetRequest::GetItemSetName() const
    {
        return ItemSetNameValue;
    }

    TOptional<FString> FConsumeItemSetRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FConsumeItemSetRequest> FConsumeItemSetRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FConsumeItemSetRequest>()
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
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("xGs2AccessToken", v))
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

    TSharedPtr<FJsonObject> FConsumeItemSetRequest::ToJson() const
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
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
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