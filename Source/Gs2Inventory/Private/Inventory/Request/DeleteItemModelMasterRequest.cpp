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

#include "Inventory/Request/DeleteItemModelMasterRequest.h"

namespace Gs2::Inventory::Request
{
    FDeleteItemModelMasterRequest::FDeleteItemModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        ItemNameValue(TOptional<FString>())
    {
    }

    FDeleteItemModelMasterRequest::FDeleteItemModelMasterRequest(
        const FDeleteItemModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        ItemNameValue(From.ItemNameValue)
    {
    }

    TSharedPtr<FDeleteItemModelMasterRequest> FDeleteItemModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteItemModelMasterRequest> FDeleteItemModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteItemModelMasterRequest> FDeleteItemModelMasterRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteItemModelMasterRequest> FDeleteItemModelMasterRequest::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteItemModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteItemModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteItemModelMasterRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FDeleteItemModelMasterRequest::GetItemName() const
    {
        return ItemNameValue;
    }

    TSharedPtr<FDeleteItemModelMasterRequest> FDeleteItemModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteItemModelMasterRequest>()
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
            ->WithItemName(Data->HasField("itemName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("itemName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteItemModelMasterRequest::ToJson() const
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
        return JsonRootObject;
    }
}