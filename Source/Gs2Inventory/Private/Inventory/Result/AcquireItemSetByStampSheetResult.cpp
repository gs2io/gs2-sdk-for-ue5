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

#include "Inventory/Result/AcquireItemSetByStampSheetResult.h"

namespace Gs2::Inventory::Result
{
    FAcquireItemSetByStampSheetResult::FAcquireItemSetByStampSheetResult():
        ItemsValue(nullptr),
        ItemModelValue(nullptr),
        InventoryValue(nullptr),
        OverflowCountValue(TOptional<int64>())
    {
    }

    FAcquireItemSetByStampSheetResult::FAcquireItemSetByStampSheetResult(
        const FAcquireItemSetByStampSheetResult& From
    ):
        ItemsValue(From.ItemsValue),
        ItemModelValue(From.ItemModelValue),
        InventoryValue(From.InventoryValue),
        OverflowCountValue(From.OverflowCountValue)
    {
    }

    TSharedPtr<FAcquireItemSetByStampSheetResult> FAcquireItemSetByStampSheetResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByStampSheetResult> FAcquireItemSetByStampSheetResult::WithItemModel(
        const TSharedPtr<Model::FItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByStampSheetResult> FAcquireItemSetByStampSheetResult::WithInventory(
        const TSharedPtr<Model::FInventory> Inventory
    )
    {
        this->InventoryValue = Inventory;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByStampSheetResult> FAcquireItemSetByStampSheetResult::WithOverflowCount(
        const TOptional<int64> OverflowCount
    )
    {
        this->OverflowCountValue = OverflowCount;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> FAcquireItemSetByStampSheetResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<Model::FItemModel> FAcquireItemSetByStampSheetResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<Model::FInventory> FAcquireItemSetByStampSheetResult::GetInventory() const
    {
        if (!InventoryValue.IsValid())
        {
            return nullptr;
        }
        return InventoryValue;
    }

    TOptional<int64> FAcquireItemSetByStampSheetResult::GetOverflowCount() const
    {
        return OverflowCountValue;
    }

    FString FAcquireItemSetByStampSheetResult::GetOverflowCountString() const
    {
        if (!OverflowCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), OverflowCountValue.GetValue());
    }

    TSharedPtr<FAcquireItemSetByStampSheetResult> FAcquireItemSetByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireItemSetByStampSheetResult>()
            ->WithItems(Data->HasField("items") ? [Data]() -> TSharedPtr<TArray<Model::FItemSetPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FItemSetPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("items") && Data->HasTypedField<EJson::Array>("items"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("items"))
                        {
                            v->Add(Model::FItemSet::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithItemModel(Data->HasField("itemModel") ? [Data]() -> Model::FItemModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("itemModel"))
                    {
                        return nullptr;
                    }
                    return Model::FItemModel::FromJson(Data->GetObjectField("itemModel"));
                 }() : nullptr)
            ->WithInventory(Data->HasField("inventory") ? [Data]() -> Model::FInventoryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("inventory"))
                    {
                        return nullptr;
                    }
                    return Model::FInventory::FromJson(Data->GetObjectField("inventory"));
                 }() : nullptr)
            ->WithOverflowCount(Data->HasField("overflowCount") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("overflowCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FAcquireItemSetByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemsValue != nullptr && ItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("items", v);
        }
        if (ItemModelValue != nullptr && ItemModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("itemModel", ItemModelValue->ToJson());
        }
        if (InventoryValue != nullptr && InventoryValue.IsValid())
        {
            JsonRootObject->SetObjectField("inventory", InventoryValue->ToJson());
        }
        if (OverflowCountValue.IsSet())
        {
            JsonRootObject->SetStringField("overflowCount", FString::Printf(TEXT("%lld"), OverflowCountValue.GetValue()));
        }
        return JsonRootObject;
    }
}