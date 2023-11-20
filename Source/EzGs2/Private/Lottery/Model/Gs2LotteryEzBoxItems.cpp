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

#include "Lottery/Model/Gs2LotteryEzBoxItems.h"

namespace Gs2::UE5::Lottery::Model
{

    TSharedPtr<FEzBoxItems> FEzBoxItems::WithBoxId(
        const TOptional<FString> BoxId
    )
    {
        this->BoxIdValue = BoxId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBoxItems> FEzBoxItems::WithPrizeTableName(
        const TOptional<FString> PrizeTableName
    )
    {
        this->PrizeTableNameValue = PrizeTableName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBoxItems> FEzBoxItems::WithItems(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzBoxItem>>> Items
    )
    {
        this->ItemsValue = Items;
        return SharedThis(this);
    }
    TOptional<FString> FEzBoxItems::GetBoxId() const
    {
        return BoxIdValue;
    }
    TOptional<FString> FEzBoxItems::GetPrizeTableName() const
    {
        return PrizeTableNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzBoxItem>>> FEzBoxItems::GetItems() const
    {
        return ItemsValue;
    }

    Gs2::Lottery::Model::FBoxItemsPtr FEzBoxItems::ToModel() const
    {
        return MakeShared<Gs2::Lottery::Model::FBoxItems>()
            ->WithBoxId(BoxIdValue)
            ->WithPrizeTableName(PrizeTableNameValue)
            ->WithItems([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Lottery::Model::FBoxItem>>>();
                    if (ItemsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ItemsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzBoxItems> FEzBoxItems::FromModel(const Gs2::Lottery::Model::FBoxItemsPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBoxItems>()
            ->WithBoxId(Model->GetBoxId())
            ->WithPrizeTableName(Model->GetPrizeTableName())
            ->WithItems([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzBoxItem>>>();
                    if (Model->GetItems() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetItems())
                    {
                        v->Add(FEzBoxItem::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}