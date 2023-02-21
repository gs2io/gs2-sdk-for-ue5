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

#include "Inventory/Request/UpdateItemModelMasterRequest.h"

namespace Gs2::Inventory::Request
{
    FUpdateItemModelMasterRequest::FUpdateItemModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        ItemNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        StackingLimitValue(TOptional<int64>()),
        AllowMultipleStacksValue(TOptional<bool>()),
        SortValueValue(TOptional<int32>())
    {
    }

    FUpdateItemModelMasterRequest::FUpdateItemModelMasterRequest(
        const FUpdateItemModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        ItemNameValue(From.ItemNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        StackingLimitValue(From.StackingLimitValue),
        AllowMultipleStacksValue(From.AllowMultipleStacksValue),
        SortValueValue(From.SortValueValue)
    {
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithStackingLimit(
        const TOptional<int64> StackingLimit
    )
    {
        this->StackingLimitValue = StackingLimit;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithAllowMultipleStacks(
        const TOptional<bool> AllowMultipleStacks
    )
    {
        this->AllowMultipleStacksValue = AllowMultipleStacks;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::WithSortValue(
        const TOptional<int32> SortValue
    )
    {
        this->SortValueValue = SortValue;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateItemModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateItemModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateItemModelMasterRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FUpdateItemModelMasterRequest::GetItemName() const
    {
        return ItemNameValue;
    }

    TOptional<FString> FUpdateItemModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateItemModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int64> FUpdateItemModelMasterRequest::GetStackingLimit() const
    {
        return StackingLimitValue;
    }

    FString FUpdateItemModelMasterRequest::GetStackingLimitString() const
    {
        if (!StackingLimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StackingLimitValue.GetValue());
    }

    TOptional<bool> FUpdateItemModelMasterRequest::GetAllowMultipleStacks() const
    {
        return AllowMultipleStacksValue;
    }

    FString FUpdateItemModelMasterRequest::GetAllowMultipleStacksString() const
    {
        if (!AllowMultipleStacksValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowMultipleStacksValue.GetValue() ? "true" : "false");
    }

    TOptional<int32> FUpdateItemModelMasterRequest::GetSortValue() const
    {
        return SortValueValue;
    }

    FString FUpdateItemModelMasterRequest::GetSortValueString() const
    {
        if (!SortValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), SortValueValue.GetValue());
    }

    TSharedPtr<FUpdateItemModelMasterRequest> FUpdateItemModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateItemModelMasterRequest>()
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
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithStackingLimit(Data->HasField("stackingLimit") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("stackingLimit", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithAllowMultipleStacks(Data->HasField("allowMultipleStacks") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("allowMultipleStacks", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
            ->WithSortValue(Data->HasField("sortValue") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("sortValue", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUpdateItemModelMasterRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (StackingLimitValue.IsSet())
        {
            JsonRootObject->SetStringField("stackingLimit", FString::Printf(TEXT("%lld"), StackingLimitValue.GetValue()));
        }
        if (AllowMultipleStacksValue.IsSet())
        {
            JsonRootObject->SetBoolField("allowMultipleStacks", AllowMultipleStacksValue.GetValue());
        }
        if (SortValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("sortValue", SortValueValue.GetValue());
        }
        return JsonRootObject;
    }
}