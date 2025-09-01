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

#include "Inventory/Result/VerifyInventoryCurrentMaxCapacityResult.h"

namespace Gs2::Inventory::Result
{
    FVerifyInventoryCurrentMaxCapacityResult::FVerifyInventoryCurrentMaxCapacityResult():
        ItemValue(nullptr)
    {
    }

    FVerifyInventoryCurrentMaxCapacityResult::FVerifyInventoryCurrentMaxCapacityResult(
        const FVerifyInventoryCurrentMaxCapacityResult& From
    ):
        ItemValue(From.ItemValue)
    {
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityResult> FVerifyInventoryCurrentMaxCapacityResult::WithItem(
        const TSharedPtr<Model::FInventory> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<Model::FInventory> FVerifyInventoryCurrentMaxCapacityResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<FVerifyInventoryCurrentMaxCapacityResult> FVerifyInventoryCurrentMaxCapacityResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVerifyInventoryCurrentMaxCapacityResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FInventoryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FInventory::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FVerifyInventoryCurrentMaxCapacityResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        return JsonRootObject;
    }
}