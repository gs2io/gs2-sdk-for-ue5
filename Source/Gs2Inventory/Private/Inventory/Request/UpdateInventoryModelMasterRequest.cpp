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

#include "Inventory/Request/UpdateInventoryModelMasterRequest.h"

namespace Gs2::Inventory::Request
{
    FUpdateInventoryModelMasterRequest::FUpdateInventoryModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        InitialCapacityValue(TOptional<int32>()),
        MaxCapacityValue(TOptional<int32>()),
        ProtectReferencedItemValue(TOptional<bool>())
    {
    }

    FUpdateInventoryModelMasterRequest::FUpdateInventoryModelMasterRequest(
        const FUpdateInventoryModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        InventoryNameValue(From.InventoryNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        InitialCapacityValue(From.InitialCapacityValue),
        MaxCapacityValue(From.MaxCapacityValue),
        ProtectReferencedItemValue(From.ProtectReferencedItemValue)
    {
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::WithProtectReferencedItem(
        const TOptional<bool> ProtectReferencedItem
    )
    {
        this->ProtectReferencedItemValue = ProtectReferencedItem;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateInventoryModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateInventoryModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateInventoryModelMasterRequest::GetInventoryName() const
    {
        return InventoryNameValue;
    }

    TOptional<FString> FUpdateInventoryModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateInventoryModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FUpdateInventoryModelMasterRequest::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FUpdateInventoryModelMasterRequest::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }

    TOptional<int32> FUpdateInventoryModelMasterRequest::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FUpdateInventoryModelMasterRequest::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }

    TOptional<bool> FUpdateInventoryModelMasterRequest::GetProtectReferencedItem() const
    {
        return ProtectReferencedItemValue;
    }

    FString FUpdateInventoryModelMasterRequest::GetProtectReferencedItemString() const
    {
        if (!ProtectReferencedItemValue.IsSet())
        {
            return FString("null");
        }
        return FString(ProtectReferencedItemValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FUpdateInventoryModelMasterRequest> FUpdateInventoryModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateInventoryModelMasterRequest>()
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithInitialCapacity(Data->HasField("initialCapacity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("initialCapacity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithMaxCapacity(Data->HasField("maxCapacity") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("maxCapacity", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithProtectReferencedItem(Data->HasField("protectReferencedItem") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("protectReferencedItem", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FUpdateInventoryModelMasterRequest::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (InitialCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("initialCapacity", InitialCapacityValue.GetValue());
        }
        if (MaxCapacityValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxCapacity", MaxCapacityValue.GetValue());
        }
        if (ProtectReferencedItemValue.IsSet())
        {
            JsonRootObject->SetBoolField("protectReferencedItem", ProtectReferencedItemValue.GetValue());
        }
        return JsonRootObject;
    }
}