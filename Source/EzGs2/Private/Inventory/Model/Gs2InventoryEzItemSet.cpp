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

#include "EzGs2/Public/Inventory/Model/Gs2InventoryEzItemSet.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzItemSet> FEzItemSet::WithItemSetId(
        const TOptional<FString> ItemSetId
    )
    {
        this->ItemSetIdValue = ItemSetId;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemSet> FEzItemSet::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemSet> FEzItemSet::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemSet> FEzItemSet::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemSet> FEzItemSet::WithCount(
        const TOptional<int64> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemSet> FEzItemSet::WithSortValue(
        const TOptional<int32> SortValue
    )
    {
        this->SortValueValue = SortValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemSet> FEzItemSet::WithExpiresAt(
        const TOptional<int64> ExpiresAt
    )
    {
        this->ExpiresAtValue = ExpiresAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzItemSet::GetItemSetId() const
    {
        return ItemSetIdValue;
    }
    TOptional<FString> FEzItemSet::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzItemSet::GetInventoryName() const
    {
        return InventoryNameValue;
    }
    TOptional<FString> FEzItemSet::GetItemName() const
    {
        return ItemNameValue;
    }
    TOptional<int64> FEzItemSet::GetCount() const
    {
        return CountValue;
    }

    FString FEzItemSet::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CountValue.GetValue());
    }
    TOptional<int32> FEzItemSet::GetSortValue() const
    {
        return SortValueValue;
    }

    FString FEzItemSet::GetSortValueString() const
    {
        if (!SortValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SortValueValue.GetValue());
    }
    TOptional<int64> FEzItemSet::GetExpiresAt() const
    {
        return ExpiresAtValue;
    }

    FString FEzItemSet::GetExpiresAtString() const
    {
        if (!ExpiresAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpiresAtValue.GetValue());
    }

    Gs2::Inventory::Model::FItemSetPtr FEzItemSet::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FItemSet>()
            ->WithItemSetId(ItemSetIdValue)
            ->WithName(NameValue)
            ->WithInventoryName(InventoryNameValue)
            ->WithItemName(ItemNameValue)
            ->WithCount(CountValue)
            ->WithSortValue(SortValueValue)
            ->WithExpiresAt(ExpiresAtValue);
    }

    TSharedPtr<FEzItemSet> FEzItemSet::FromModel(const Gs2::Inventory::Model::FItemSetPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzItemSet>()
            ->WithItemSetId(Model->GetItemSetId())
            ->WithName(Model->GetName())
            ->WithInventoryName(Model->GetInventoryName())
            ->WithItemName(Model->GetItemName())
            ->WithCount(Model->GetCount())
            ->WithSortValue(Model->GetSortValue())
            ->WithExpiresAt(Model->GetExpiresAt());
    }
}