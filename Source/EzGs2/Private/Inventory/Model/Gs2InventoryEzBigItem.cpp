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

#include "Inventory/Model/Gs2InventoryEzBigItem.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzBigItem> FEzBigItem::WithItemId(
        const TOptional<FString> ItemId
    )
    {
        this->ItemIdValue = ItemId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBigItem> FEzBigItem::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBigItem> FEzBigItem::WithCount(
        const TOptional<FString> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FEzBigItem::GetItemId() const
    {
        return ItemIdValue;
    }
    TOptional<FString> FEzBigItem::GetItemName() const
    {
        return ItemNameValue;
    }
    TOptional<FString> FEzBigItem::GetCount() const
    {
        return CountValue;
    }

    Gs2::Inventory::Model::FBigItemPtr FEzBigItem::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FBigItem>()
            ->WithItemId(ItemIdValue)
            ->WithItemName(ItemNameValue)
            ->WithCount(CountValue);
    }

    TSharedPtr<FEzBigItem> FEzBigItem::FromModel(const Gs2::Inventory::Model::FBigItemPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBigItem>()
            ->WithItemId(Model->GetItemId())
            ->WithItemName(Model->GetItemName())
            ->WithCount(Model->GetCount());
    }
}