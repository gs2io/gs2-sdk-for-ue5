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

#include "Inventory/Model/InventoryModelMaster.h"

namespace Gs2::Inventory::Model
{
    FInventoryModelMaster::FInventoryModelMaster():
        InventoryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        InitialCapacityValue(TOptional<int32>()),
        MaxCapacityValue(TOptional<int32>()),
        ProtectReferencedItemValue(TOptional<bool>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FInventoryModelMaster::FInventoryModelMaster(
        const FInventoryModelMaster& From
    ):
        InventoryModelIdValue(From.InventoryModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        InitialCapacityValue(From.InitialCapacityValue),
        MaxCapacityValue(From.MaxCapacityValue),
        ProtectReferencedItemValue(From.ProtectReferencedItemValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithInventoryModelId(
        const TOptional<FString> InventoryModelId
    )
    {
        this->InventoryModelIdValue = InventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithProtectReferencedItem(
        const TOptional<bool> ProtectReferencedItem
    )
    {
        this->ProtectReferencedItemValue = ProtectReferencedItem;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FInventoryModelMaster::GetInventoryModelId() const
    {
        return InventoryModelIdValue;
    }
    TOptional<FString> FInventoryModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FInventoryModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FInventoryModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<int32> FInventoryModelMaster::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FInventoryModelMaster::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }
    TOptional<int32> FInventoryModelMaster::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FInventoryModelMaster::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }
    TOptional<bool> FInventoryModelMaster::GetProtectReferencedItem() const
    {
        return ProtectReferencedItemValue;
    }

    FString FInventoryModelMaster::GetProtectReferencedItemString() const
    {
        if (!ProtectReferencedItemValue.IsSet())
        {
            return FString("null");
        }
        return FString(ProtectReferencedItemValue.GetValue() ? "true" : "false");
    }
    TOptional<int64> FInventoryModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FInventoryModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FInventoryModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FInventoryModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FInventoryModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FInventoryModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FInventoryModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventoryModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventoryModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventoryModelMaster::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FInventoryModelMaster> FInventoryModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FInventoryModelMaster>()
            ->WithInventoryModelId(Data->HasField("inventoryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("inventoryModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("description", v))
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
                }() : TOptional<bool>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FInventoryModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (InventoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("inventoryModelId", InventoryModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
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
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FInventoryModelMaster::TypeName = "InventoryModelMaster";
}