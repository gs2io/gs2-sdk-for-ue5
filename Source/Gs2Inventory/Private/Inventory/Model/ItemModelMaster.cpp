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

#include "Inventory/Model/ItemModelMaster.h"

namespace Gs2::Inventory::Model
{
    FItemModelMaster::FItemModelMaster():
        ItemModelIdValue(TOptional<FString>()),
        InventoryNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        StackingLimitValue(TOptional<int64>()),
        AllowMultipleStacksValue(TOptional<bool>()),
        SortValueValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FItemModelMaster::FItemModelMaster(
        const FItemModelMaster& From
    ):
        ItemModelIdValue(From.ItemModelIdValue),
        InventoryNameValue(From.InventoryNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        StackingLimitValue(From.StackingLimitValue),
        AllowMultipleStacksValue(From.AllowMultipleStacksValue),
        SortValueValue(From.SortValueValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithItemModelId(
        const TOptional<FString> ItemModelId
    )
    {
        this->ItemModelIdValue = ItemModelId;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithStackingLimit(
        const TOptional<int64> StackingLimit
    )
    {
        this->StackingLimitValue = StackingLimit;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithAllowMultipleStacks(
        const TOptional<bool> AllowMultipleStacks
    )
    {
        this->AllowMultipleStacksValue = AllowMultipleStacks;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithSortValue(
        const TOptional<int32> SortValue
    )
    {
        this->SortValueValue = SortValue;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FItemModelMaster::GetItemModelId() const
    {
        return ItemModelIdValue;
    }
    TOptional<FString> FItemModelMaster::GetInventoryName() const
    {
        return InventoryNameValue;
    }
    TOptional<FString> FItemModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FItemModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FItemModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FItemModelMaster::GetStackingLimit() const
    {
        return StackingLimitValue;
    }

    FString FItemModelMaster::GetStackingLimitString() const
    {
        if (!StackingLimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StackingLimitValue.GetValue());
    }
    TOptional<bool> FItemModelMaster::GetAllowMultipleStacks() const
    {
        return AllowMultipleStacksValue;
    }

    FString FItemModelMaster::GetAllowMultipleStacksString() const
    {
        if (!AllowMultipleStacksValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowMultipleStacksValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FItemModelMaster::GetSortValue() const
    {
        return SortValueValue;
    }

    FString FItemModelMaster::GetSortValueString() const
    {
        if (!SortValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SortValueValue.GetValue());
    }
    TOptional<int64> FItemModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FItemModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FItemModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FItemModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FItemModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModelMaster::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModelMaster::GetItemNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FItemModelMaster> FItemModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FItemModelMaster>()
            ->WithItemModelId(Data->HasField("itemModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("itemModelId", v))
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
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
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
                }() : TOptional<int32>())
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FItemModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("itemModelId", ItemModelIdValue.GetValue());
        }
        if (InventoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("inventoryName", InventoryNameValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
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
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FItemModelMaster::TypeName = "ItemModelMaster";
}