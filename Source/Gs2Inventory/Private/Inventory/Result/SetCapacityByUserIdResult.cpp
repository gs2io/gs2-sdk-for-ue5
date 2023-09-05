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

#include "Inventory/Result/SetCapacityByUserIdResult.h"

namespace Gs2::Inventory::Result
{
    FSetCapacityByUserIdResult::FSetCapacityByUserIdResult():
        ItemValue(nullptr),
        OldValue(nullptr)
    {
    }

    FSetCapacityByUserIdResult::FSetCapacityByUserIdResult(
        const FSetCapacityByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue)
    {
    }

    TSharedPtr<FSetCapacityByUserIdResult> FSetCapacityByUserIdResult::WithItem(
        const TSharedPtr<Model::FInventory> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetCapacityByUserIdResult> FSetCapacityByUserIdResult::WithOld(
        const TSharedPtr<Model::FInventory> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<Model::FInventory> FSetCapacityByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FInventory> FSetCapacityByUserIdResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<FSetCapacityByUserIdResult> FSetCapacityByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetCapacityByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FInventoryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FInventory::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithOld(Data->HasField("old") ? [Data]() -> Model::FInventoryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("old"))
                    {
                        return nullptr;
                    }
                    return Model::FInventory::FromJson(Data->GetObjectField("old"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetCapacityByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (OldValue != nullptr && OldValue.IsValid())
        {
            JsonRootObject->SetObjectField("old", OldValue->ToJson());
        }
        return JsonRootObject;
    }
}