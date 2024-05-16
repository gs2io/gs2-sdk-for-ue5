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

#include "Inventory/Model/InventoryModel.h"

namespace Gs2::Inventory::Model
{
    FInventoryModel::FInventoryModel():
        InventoryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        InitialCapacityValue(TOptional<int32>()),
        MaxCapacityValue(TOptional<int32>()),
        ProtectReferencedItemValue(TOptional<bool>()),
        ItemModelsValue(nullptr)
    {
    }

    FInventoryModel::FInventoryModel(
        const FInventoryModel& From
    ):
        InventoryModelIdValue(From.InventoryModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        InitialCapacityValue(From.InitialCapacityValue),
        MaxCapacityValue(From.MaxCapacityValue),
        ProtectReferencedItemValue(From.ProtectReferencedItemValue),
        ItemModelsValue(From.ItemModelsValue)
    {
    }

    TSharedPtr<FInventoryModel> FInventoryModel::WithInventoryModelId(
        const TOptional<FString> InventoryModelId
    )
    {
        this->InventoryModelIdValue = InventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModel> FInventoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModel> FInventoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModel> FInventoryModel::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModel> FInventoryModel::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModel> FInventoryModel::WithProtectReferencedItem(
        const TOptional<bool> ProtectReferencedItem
    )
    {
        this->ProtectReferencedItemValue = ProtectReferencedItem;
        return SharedThis(this);
    }

    TSharedPtr<FInventoryModel> FInventoryModel::WithItemModels(
        const TSharedPtr<TArray<TSharedPtr<Model::FItemModel>>> ItemModels
    )
    {
        this->ItemModelsValue = ItemModels;
        return SharedThis(this);
    }
    TOptional<FString> FInventoryModel::GetInventoryModelId() const
    {
        return InventoryModelIdValue;
    }
    TOptional<FString> FInventoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FInventoryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FInventoryModel::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FInventoryModel::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }
    TOptional<int32> FInventoryModel::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FInventoryModel::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }
    TOptional<bool> FInventoryModel::GetProtectReferencedItem() const
    {
        return ProtectReferencedItemValue;
    }

    FString FInventoryModel::GetProtectReferencedItemString() const
    {
        if (!ProtectReferencedItemValue.IsSet())
        {
            return FString("null");
        }
        return FString(ProtectReferencedItemValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<TArray<TSharedPtr<Model::FItemModel>>> FInventoryModel::GetItemModels() const
    {
        return ItemModelsValue;
    }

    TOptional<FString> FInventoryModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventoryModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventoryModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FInventoryModel::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FInventoryModel> FInventoryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FInventoryModel>()
            ->WithInventoryModelId(Data->HasField(ANSI_TO_TCHAR("inventoryModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("inventoryModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithInitialCapacity(Data->HasField(ANSI_TO_TCHAR("initialCapacity")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("initialCapacity"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxCapacity(Data->HasField(ANSI_TO_TCHAR("maxCapacity")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maxCapacity"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithProtectReferencedItem(Data->HasField(ANSI_TO_TCHAR("protectReferencedItem")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("protectReferencedItem"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithItemModels(Data->HasField(ANSI_TO_TCHAR("itemModels")) ? [Data]() -> TSharedPtr<TArray<Model::FItemModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FItemModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("itemModels")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("itemModels")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("itemModels")))
                        {
                            v->Add(Model::FItemModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FItemModelPtr>>());
    }

    TSharedPtr<FJsonObject> FInventoryModel::ToJson() const
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
        if (ItemModelsValue != nullptr && ItemModelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemModelsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("itemModels", v);
        }
        return JsonRootObject;
    }

    FString FInventoryModel::TypeName = "InventoryModel";
}