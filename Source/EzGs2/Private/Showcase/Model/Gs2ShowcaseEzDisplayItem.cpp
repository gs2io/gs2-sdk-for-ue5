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

#include "Showcase/Model/Gs2ShowcaseEzDisplayItem.h"

namespace Gs2::UE5::Showcase::Model
{

    TSharedPtr<FEzDisplayItem> FEzDisplayItem::WithDisplayItemId(
        const TOptional<FString> DisplayItemId
    )
    {
        this->DisplayItemIdValue = DisplayItemId;
        return SharedThis(this);
    }

    TSharedPtr<FEzDisplayItem> FEzDisplayItem::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FEzDisplayItem> FEzDisplayItem::WithSalesItem(
        const TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem> SalesItem
    )
    {
        this->SalesItemValue = SalesItem;
        return SharedThis(this);
    }

    TSharedPtr<FEzDisplayItem> FEzDisplayItem::WithSalesItemGroup(
        const TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItemGroup> SalesItemGroup
    )
    {
        this->SalesItemGroupValue = SalesItemGroup;
        return SharedThis(this);
    }
    TOptional<FString> FEzDisplayItem::GetDisplayItemId() const
    {
        return DisplayItemIdValue;
    }
    TOptional<FString> FEzDisplayItem::GetType() const
    {
        return TypeValue;
    }
    TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem> FEzDisplayItem::GetSalesItem() const
    {
        return SalesItemValue;
    }
    TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItemGroup> FEzDisplayItem::GetSalesItemGroup() const
    {
        return SalesItemGroupValue;
    }

    Gs2::Showcase::Model::FDisplayItemPtr FEzDisplayItem::ToModel() const
    {
        return MakeShared<Gs2::Showcase::Model::FDisplayItem>()
            ->WithDisplayItemId(DisplayItemIdValue)
            ->WithType(TypeValue)
            ->WithSalesItem(SalesItemValue == nullptr ? nullptr : SalesItemValue->ToModel())
            ->WithSalesItemGroup(SalesItemGroupValue == nullptr ? nullptr : SalesItemGroupValue->ToModel());
    }

    TSharedPtr<FEzDisplayItem> FEzDisplayItem::FromModel(const Gs2::Showcase::Model::FDisplayItemPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzDisplayItem>()
            ->WithDisplayItemId(Model->GetDisplayItemId())
            ->WithType(Model->GetType())
            ->WithSalesItem(Model->GetSalesItem() != nullptr ? Gs2::UE5::Showcase::Model::FEzSalesItem::FromModel(Model->GetSalesItem()) : nullptr)
            ->WithSalesItemGroup(Model->GetSalesItemGroup() != nullptr ? Gs2::UE5::Showcase::Model::FEzSalesItemGroup::FromModel(Model->GetSalesItemGroup()) : nullptr);
    }
}