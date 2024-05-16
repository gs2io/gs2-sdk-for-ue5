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

#include "Inventory/Result/DeleteReferenceOfResult.h"

namespace Gs2::Inventory::Result
{
    FDeleteReferenceOfResult::FDeleteReferenceOfResult():
        ItemValue(TOptional<FString>()),
        ItemSetValue(nullptr),
        ItemModelValue(nullptr),
        InventoryValue(nullptr)
    {
    }

    FDeleteReferenceOfResult::FDeleteReferenceOfResult(
        const FDeleteReferenceOfResult& From
    ):
        ItemValue(From.ItemValue),
        ItemSetValue(From.ItemSetValue),
        ItemModelValue(From.ItemModelValue),
        InventoryValue(From.InventoryValue)
    {
    }

    TSharedPtr<FDeleteReferenceOfResult> FDeleteReferenceOfResult::WithItem(
        const TOptional<FString> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteReferenceOfResult> FDeleteReferenceOfResult::WithItemSet(
        const TSharedPtr<Model::FItemSet> ItemSet
    )
    {
        this->ItemSetValue = ItemSet;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteReferenceOfResult> FDeleteReferenceOfResult::WithItemModel(
        const TSharedPtr<Model::FItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteReferenceOfResult> FDeleteReferenceOfResult::WithInventory(
        const TSharedPtr<Model::FInventory> Inventory
    )
    {
        this->InventoryValue = Inventory;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteReferenceOfResult::GetItem() const
    {
        return ItemValue;
    }

    TSharedPtr<Model::FItemSet> FDeleteReferenceOfResult::GetItemSet() const
    {
        if (!ItemSetValue.IsValid())
        {
            return nullptr;
        }
        return ItemSetValue;
    }

    TSharedPtr<Model::FItemModel> FDeleteReferenceOfResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<Model::FInventory> FDeleteReferenceOfResult::GetInventory() const
    {
        if (!InventoryValue.IsValid())
        {
            return nullptr;
        }
        return InventoryValue;
    }

    TSharedPtr<FDeleteReferenceOfResult> FDeleteReferenceOfResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteReferenceOfResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("item"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithItemSet(Data->HasField(ANSI_TO_TCHAR("itemSet")) ? [Data]() -> Model::FItemSetPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("itemSet")))
                    {
                        return nullptr;
                    }
                    return Model::FItemSet::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("itemSet")));
                 }() : nullptr)
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
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDeleteReferenceOfResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue.IsSet())
        {
            JsonRootObject->SetStringField("item", ItemValue.GetValue());
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