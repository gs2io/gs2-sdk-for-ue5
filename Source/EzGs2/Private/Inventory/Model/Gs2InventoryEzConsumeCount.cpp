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

#include "Inventory/Model/Gs2InventoryEzConsumeCount.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzConsumeCount> FEzConsumeCount::WithItemName(
        const TOptional<FString> ItemName
    )
    {
        this->ItemNameValue = ItemName;
        return SharedThis(this);
    }

    TSharedPtr<FEzConsumeCount> FEzConsumeCount::WithCount(
        const TOptional<int64> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FEzConsumeCount::GetItemName() const
    {
        return ItemNameValue;
    }
    TOptional<int64> FEzConsumeCount::GetCount() const
    {
        return CountValue;
    }

    FString FEzConsumeCount::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CountValue.GetValue());
    }

    Gs2::Inventory::Model::FConsumeCountPtr FEzConsumeCount::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FConsumeCount>()
            ->WithItemName(ItemNameValue)
            ->WithCount(CountValue);
    }

    TSharedPtr<FEzConsumeCount> FEzConsumeCount::FromModel(const Gs2::Inventory::Model::FConsumeCountPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzConsumeCount>()
            ->WithItemName(Model->GetItemName())
            ->WithCount(Model->GetCount());
    }
}