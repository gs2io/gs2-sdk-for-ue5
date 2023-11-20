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

#include "Showcase/Model/Gs2ShowcaseEzSalesItem.h"

namespace Gs2::UE5::Showcase::Model
{

    TSharedPtr<FEzSalesItem> FEzSalesItem::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSalesItem> FEzSalesItem::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzSalesItem> FEzSalesItem::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzSalesItem> FEzSalesItem::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }
    TOptional<FString> FEzSalesItem::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSalesItem::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> FEzSalesItem::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> FEzSalesItem::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }

    Gs2::Showcase::Model::FSalesItemPtr FEzSalesItem::ToModel() const
    {
        return MakeShared<Gs2::Showcase::Model::FSalesItem>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Showcase::Model::FConsumeAction>>>();
                    if (ConsumeActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ConsumeActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Showcase::Model::FAcquireAction>>>();
                    if (AcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzSalesItem> FEzSalesItem::FromModel(const Gs2::Showcase::Model::FSalesItemPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSalesItem>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConsumeAction>>>();
                    if (Model->GetConsumeActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetConsumeActions())
                    {
                        v->Add(FEzConsumeAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}