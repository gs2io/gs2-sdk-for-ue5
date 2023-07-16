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

#pragma once

#include "CoreMinimal.h"
#include "Showcase/Model/RandomDisplayItem.h"
#include "Gs2ShowcaseEzConsumeAction.h"
#include "Gs2ShowcaseEzAcquireAction.h"

namespace Gs2::UE5::Showcase::Model
{
	class EZGS2_API FEzRandomDisplayItem final : public TSharedFromThis<FEzRandomDisplayItem>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> AcquireActionsValue;
        TOptional<int32> CurrentPurchaseCountValue;
        TOptional<int32> MaximumPurchaseCountValue;

	public:
        TSharedPtr<FEzRandomDisplayItem> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRandomDisplayItem> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRandomDisplayItem> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> ConsumeActions);
        TSharedPtr<FEzRandomDisplayItem> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> AcquireActions);
        TSharedPtr<FEzRandomDisplayItem> WithCurrentPurchaseCount(const TOptional<int32> CurrentPurchaseCount);
        TSharedPtr<FEzRandomDisplayItem> WithMaximumPurchaseCount(const TOptional<int32> MaximumPurchaseCount);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> GetConsumeActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> GetAcquireActions() const;

        TOptional<int32> GetCurrentPurchaseCount() const;
        FString GetCurrentPurchaseCountString() const;

        TOptional<int32> GetMaximumPurchaseCount() const;
        FString GetMaximumPurchaseCountString() const;

        Gs2::Showcase::Model::FRandomDisplayItemPtr ToModel() const;
        static TSharedPtr<FEzRandomDisplayItem> FromModel(Gs2::Showcase::Model::FRandomDisplayItemPtr Model);
    };
    typedef TSharedPtr<FEzRandomDisplayItem> FEzRandomDisplayItemPtr;
}