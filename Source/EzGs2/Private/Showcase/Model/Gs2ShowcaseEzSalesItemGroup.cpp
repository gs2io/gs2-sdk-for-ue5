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

#include "Showcase/Model/Gs2ShowcaseEzSalesItemGroup.h"

namespace Gs2::UE5::Showcase::Model
{

    TSharedPtr<FEzSalesItemGroup> FEzSalesItemGroup::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSalesItemGroup> FEzSalesItemGroup::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzSalesItemGroup> FEzSalesItemGroup::WithSalesItems(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem>>> SalesItems
    )
    {
        this->SalesItemsValue = SalesItems;
        return SharedThis(this);
    }
    TOptional<FString> FEzSalesItemGroup::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSalesItemGroup::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem>>> FEzSalesItemGroup::GetSalesItems() const
    {
        return SalesItemsValue;
    }

    Gs2::Showcase::Model::FSalesItemGroupPtr FEzSalesItemGroup::ToModel() const
    {
        return MakeShared<Gs2::Showcase::Model::FSalesItemGroup>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithSalesItems([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Showcase::Model::FSalesItem>>>();
                    if (SalesItemsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *SalesItemsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzSalesItemGroup> FEzSalesItemGroup::FromModel(const Gs2::Showcase::Model::FSalesItemGroupPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSalesItemGroup>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithSalesItems([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzSalesItem>>>();
                    if (Model->GetSalesItems() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetSalesItems())
                    {
                        v->Add(FEzSalesItem::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}