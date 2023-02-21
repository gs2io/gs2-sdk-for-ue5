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

#include "Inventory/Result/VerifyReferenceOfByStampTaskResult.h"

namespace Gs2::Inventory::Result
{
    FVerifyReferenceOfByStampTaskResult::FVerifyReferenceOfByStampTaskResult():
        ItemValue(nullptr),
        ItemSetValue(nullptr),
        ItemModelValue(nullptr),
        InventoryValue(nullptr),
        NewContextStackValue(TOptional<FString>())
    {
    }

    FVerifyReferenceOfByStampTaskResult::FVerifyReferenceOfByStampTaskResult(
        const FVerifyReferenceOfByStampTaskResult& From
    ):
        ItemValue(From.ItemValue),
        ItemSetValue(From.ItemSetValue),
        ItemModelValue(From.ItemModelValue),
        InventoryValue(From.InventoryValue),
        NewContextStackValue(From.NewContextStackValue)
    {
    }

    TSharedPtr<FVerifyReferenceOfByStampTaskResult> FVerifyReferenceOfByStampTaskResult::WithItem(
        const TSharedPtr<TArray<FString>> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByStampTaskResult> FVerifyReferenceOfByStampTaskResult::WithItemSet(
        const TSharedPtr<Model::FItemSet> ItemSet
    )
    {
        this->ItemSetValue = ItemSet;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByStampTaskResult> FVerifyReferenceOfByStampTaskResult::WithItemModel(
        const TSharedPtr<Model::FItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByStampTaskResult> FVerifyReferenceOfByStampTaskResult::WithInventory(
        const TSharedPtr<Model::FInventory> Inventory
    )
    {
        this->InventoryValue = Inventory;
        return SharedThis(this);
    }

    TSharedPtr<FVerifyReferenceOfByStampTaskResult> FVerifyReferenceOfByStampTaskResult::WithNewContextStack(
        const TOptional<FString> NewContextStack
    )
    {
        this->NewContextStackValue = NewContextStack;
        return SharedThis(this);
    }

    TSharedPtr<TArray<FString>> FVerifyReferenceOfByStampTaskResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FItemSet> FVerifyReferenceOfByStampTaskResult::GetItemSet() const
    {
        if (!ItemSetValue.IsValid())
        {
            return nullptr;
        }
        return ItemSetValue;
    }

    TSharedPtr<Model::FItemModel> FVerifyReferenceOfByStampTaskResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<Model::FInventory> FVerifyReferenceOfByStampTaskResult::GetInventory() const
    {
        if (!InventoryValue.IsValid())
        {
            return nullptr;
        }
        return InventoryValue;
    }

    TOptional<FString> FVerifyReferenceOfByStampTaskResult::GetNewContextStack() const
    {
        return NewContextStackValue;
    }

    TSharedPtr<FVerifyReferenceOfByStampTaskResult> FVerifyReferenceOfByStampTaskResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyReferenceOfByStampTaskResult>()
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
                 }() : nullptr)
            ->WithNewContextStack(Data->HasField("newContextStack") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("newContextStack", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVerifyReferenceOfByStampTaskResult::ToJson() const
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
        if (NewContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("newContextStack", NewContextStackValue.GetValue());
        }
        return JsonRootObject;
    }
}