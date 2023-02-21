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

#include "Inventory/Result/VerifyReferenceOfResult.h"

namespace Gs2::Inventory::Result
{
    FVerifyReferenceOfResult::FVerifyReferenceOfResult():
        ItemValue(nullptr),
        ItemSetValue(nullptr),
        ItemModelValue(nullptr),
        InventoryValue(nullptr)
    {
    }

    FVerifyReferenceOfResult::FVerifyReferenceOfResult(
        const FVerifyReferenceOfResult& From
    ):
        ItemValue(From.ItemValue),
        ItemSetValue(From.ItemSetValue),
        ItemModelValue(From.ItemModelValue),
        InventoryValue(From.InventoryValue)
    {
    }

    TSharedPtr<FVerifyReferenceOfResult> FVerifyReferenceOfResult::WithItem(
        const TSharedPtr<TArray<FString>> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfResult> FVerifyReferenceOfResult::WithItemSet(
        const TSharedPtr<Model::FItemSet> ItemSet
    )
    {
        this->ItemSetValue = ItemSet;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfResult> FVerifyReferenceOfResult::WithItemModel(
        const TSharedPtr<Model::FItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfResult> FVerifyReferenceOfResult::WithInventory(
        const TSharedPtr<Model::FInventory> Inventory
    )
    {
        this->InventoryValue = Inventory;
        return SharedThis(this);
    }

    TSharedPtr<TArray<FString>> FVerifyReferenceOfResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FItemSet> FVerifyReferenceOfResult::GetItemSet() const
    {
        if (!ItemSetValue.IsValid())
        {
            return nullptr;
        }
        return ItemSetValue;
    }

    TSharedPtr<Model::FItemModel> FVerifyReferenceOfResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<Model::FInventory> FVerifyReferenceOfResult::GetInventory() const
    {
        if (!InventoryValue.IsValid())
        {
            return nullptr;
        }
        return InventoryValue;
    }

    TSharedPtr<FVerifyReferenceOfResult> FVerifyReferenceOfResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyReferenceOfResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> TSharedPtr<TArray<FString>>
                 {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>("item") && Data->HasTypedField<EJson::Array>("item"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("item"))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : nullptr)
            ->WithItemSet(Data->HasField("itemSet") ? [Data]() -> Model::FItemSetPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("itemSet"))
                    {
                        return nullptr;
                    }
                    return Model::FItemSet::FromJson(Data->GetObjectField("itemSet"));
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
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FVerifyReferenceOfResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("item", v);
        }
        if (ItemSetValue != nullptr && ItemSetValue.IsValid())
        {
            JsonRootObject->SetObjectField("itemSet", ItemSetValue->ToJson());
        }
        if (ItemModelValue != nullptr && ItemModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("itemModel", ItemModelValue->ToJson());
        }
        if (InventoryValue != nullptr && InventoryValue.IsValid())
        {
            JsonRootObject->SetObjectField("inventory", InventoryValue->ToJson());
        }
        return JsonRootObject;
    }
}