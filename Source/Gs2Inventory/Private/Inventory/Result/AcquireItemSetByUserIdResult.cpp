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

#include "Inventory/Result/AcquireItemSetByUserIdResult.h"

namespace Gs2::Inventory::Result
{
    FAcquireItemSetByUserIdResult::FAcquireItemSetByUserIdResult():
        ItemsValue(nullptr),
        ItemModelValue(nullptr),
        InventoryValue(nullptr),
        OverflowCountValue(TOptional<int64>())
    {
    }

    FAcquireItemSetByUserIdResult::FAcquireItemSetByUserIdResult(
        const FAcquireItemSetByUserIdResult& From
    ):
        ItemsValue(From.ItemsValue),
        ItemModelValue(From.ItemModelValue),
        InventoryValue(From.InventoryValue),
        OverflowCountValue(From.OverflowCountValue)
    {
    }

    TSharedPtr<FAcquireItemSetByUserIdResult> FAcquireItemSetByUserIdResult::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdResult> FAcquireItemSetByUserIdResult::WithItemModel(
        const TSharedPtr<Model::FItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdResult> FAcquireItemSetByUserIdResult::WithInventory(
        const TSharedPtr<Model::FInventory> Inventory
    )
    {
        this->InventoryValue = Inventory;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetByUserIdResult> FAcquireItemSetByUserIdResult::WithOverflowCount(
        const TOptional<int64> OverflowCount
    )
    {
        this->OverflowCountValue = OverflowCount;
        return SharedThis(this);
    }

    TSharedPtr<TArray<TSharedPtr<Model::FItemSet>>> FAcquireItemSetByUserIdResult::GetItems() const
    {
        if (!ItemsValue.IsValid())
        {
            return nullptr;
        }
        return ItemsValue;
    }

    TSharedPtr<Model::FItemModel> FAcquireItemSetByUserIdResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<Model::FInventory> FAcquireItemSetByUserIdResult::GetInventory() const
    {
        if (!InventoryValue.IsValid())
        {
            return nullptr;
        }
        return InventoryValue;
    }

    TOptional<int64> FAcquireItemSetByUserIdResult::GetOverflowCount() const
    {
        return OverflowCountValue;
    }

    FString FAcquireItemSetByUserIdResult::GetOverflowCountString() const
    {
        if (!OverflowCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), OverflowCountValue.GetValue());
    }

    TSharedPtr<FAcquireItemSetByUserIdResult> FAcquireItemSetByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireItemSetByUserIdResult>()
            ->WithItems(Data->HasField(ANSI_TO_TCHAR("items")) ? [Data]() -> TSharedPtr<TArray<Model::FItemSetPtr>>
                 {
                    auto v = MakeShared<TArray<Model::FItemSetPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("items")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("items")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("items")))
                        {
                            v->Add(Model::FItemSet::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FItemSetPtr>>())
            ->WithItemModel(Data->HasField(ANSI_TO_TCHAR("itemModel")) ? [Data]() -> Model::FItemModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("itemModel")))
                    {
                        return nullptr;
                    }
                    return Model::FItemModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("itemModel")));
                 }() : nullptr)
            ->WithInventory(Data->HasField(ANSI_TO_TCHAR("inventory")) ? [Data]() -> Model::FInventoryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("inventory")))
                    {
                        return nullptr;
                    }
                    return Model::FInventory::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("inventory")));
                 }() : nullptr)
            ->WithOverflowCount(Data->HasField(ANSI_TO_TCHAR("overflowCount")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("overflowCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FAcquireItemSetByUserIdResult::ToJson() const
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