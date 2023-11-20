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

#include "Inventory/Model/Gs2InventoryEzSimpleItem.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzSimpleItem> FEzSimpleItem::WithItemId(
        const TOptional<FString> ItemId
    )
    {
        this->ItemIdValue = ItemId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSimpleItem> FEzSimpleItem::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSimpleItem> FEzSimpleItem::WithCount(
        const TOptional<int64> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FEzSimpleItem::GetItemId() const
    {
        return ItemIdValue;
    }
    TOptional<FString> FEzSimpleItem::GetItemName() const
    {
        return ItemNameValue;
    }
    TOptional<int64> FEzSimpleItem::GetCount() const
    {
        return CountValue;
    }

    FString FEzSimpleItem::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CountValue.GetValue());
    }

    Gs2::Inventory::Model::FSimpleItemPtr FEzSimpleItem::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FSimpleItem>()
            ->WithItemId(ItemIdValue)
            ->WithItemName(ItemNameValue)
            ->WithCount(CountValue);
    }

    TSharedPtr<FEzSimpleItem> FEzSimpleItem::FromModel(const Gs2::Inventory::Model::FSimpleItemPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSimpleItem>()
            ->WithItemId(Model->GetItemId())
            ->WithItemName(Model->GetItemName())
            ->WithCount(Model->GetCount());
    }
}