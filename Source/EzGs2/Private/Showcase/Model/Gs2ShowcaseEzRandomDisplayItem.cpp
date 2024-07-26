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

#include "Showcase/Model/Gs2ShowcaseEzRandomDisplayItem.h"

namespace Gs2::UE5::Showcase::Model
{

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::WithVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzVerifyAction>>> VerifyActions
    )
    {
        this->VerifyActionsValue = VerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::WithAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> AcquireActions
    )
    {
        this->AcquireActionsValue = AcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::WithCurrentPurchaseCount(
        const TOptional<int32> CurrentPurchaseCount
    )
    {
        this->CurrentPurchaseCountValue = CurrentPurchaseCount;
        return SharedThis(this);
    }

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::WithMaximumPurchaseCount(
        const TOptional<int32> MaximumPurchaseCount
    )
    {
        this->MaximumPurchaseCountValue = MaximumPurchaseCount;
        return SharedThis(this);
    }
    TOptional<FString> FEzRandomDisplayItem::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRandomDisplayItem::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzVerifyAction>>> FEzRandomDisplayItem::GetVerifyActions() const
    {
        return VerifyActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> FEzRandomDisplayItem::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> FEzRandomDisplayItem::GetAcquireActions() const
    {
        return AcquireActionsValue;
    }
    TOptional<int32> FEzRandomDisplayItem::GetCurrentPurchaseCount() const
    {
        return CurrentPurchaseCountValue;
    }

    FString FEzRandomDisplayItem::GetCurrentPurchaseCountString() const
    {
        if (!CurrentPurchaseCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentPurchaseCountValue.GetValue());
    }
    TOptional<int32> FEzRandomDisplayItem::GetMaximumPurchaseCount() const
    {
        return MaximumPurchaseCountValue;
    }

    FString FEzRandomDisplayItem::GetMaximumPurchaseCountString() const
    {
        if (!MaximumPurchaseCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumPurchaseCountValue.GetValue());
    }

    Gs2::Showcase::Model::FRandomDisplayItemPtr FEzRandomDisplayItem::ToModel() const
    {
        return MakeShared<Gs2::Showcase::Model::FRandomDisplayItem>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithVerifyActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Showcase::Model::FVerifyAction>>>();
                    if (VerifyActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *VerifyActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
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
            )
            ->WithCurrentPurchaseCount(CurrentPurchaseCountValue)
            ->WithMaximumPurchaseCount(MaximumPurchaseCountValue);
    }

    TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItem::FromModel(const Gs2::Showcase::Model::FRandomDisplayItemPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRandomDisplayItem>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithVerifyActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzVerifyAction>>>();
                    if (Model->GetVerifyActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetVerifyActions())
                    {
                        v->Add(FEzVerifyAction::FromModel(v2));
                    }
                    return v;
                }()
            )
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
            )
            ->WithCurrentPurchaseCount(Model->GetCurrentPurchaseCount())
            ->WithMaximumPurchaseCount(Model->GetMaximumPurchaseCount());
    }
}