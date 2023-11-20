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

#include "Showcase/Model/Gs2ShowcaseEzShowcase.h"

namespace Gs2::UE5::Showcase::Model
{

    TSharedPtr<FEzShowcase> FEzShowcase::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzShowcase> FEzShowcase::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzShowcase> FEzShowcase::WithDisplayItems(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItem>>> DisplayItems
    )
    {
        this->DisplayItemsValue = DisplayItems;
        return SharedThis(this);
    }
    TOptional<FString> FEzShowcase::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzShowcase::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItem>>> FEzShowcase::GetDisplayItems() const
    {
        return DisplayItemsValue;
    }

    Gs2::Showcase::Model::FShowcasePtr FEzShowcase::ToModel() const
    {
        return MakeShared<Gs2::Showcase::Model::FShowcase>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithDisplayItems([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Showcase::Model::FDisplayItem>>>();
                    if (DisplayItemsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *DisplayItemsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzShowcase> FEzShowcase::FromModel(const Gs2::Showcase::Model::FShowcasePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzShowcase>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithDisplayItems([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzDisplayItem>>>();
                    if (Model->GetDisplayItems() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetDisplayItems())
                    {
                        v->Add(FEzDisplayItem::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}