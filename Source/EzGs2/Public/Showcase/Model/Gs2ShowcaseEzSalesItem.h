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
#include "Showcase/Model/SalesItem.h"
#include "Gs2ShowcaseEzConsumeAction.h"
#include "Gs2ShowcaseEzAcquireAction.h"

namespace Gs2::UE5::Showcase::Model
{
	class EZGS2_API FEzSalesItem final : public TSharedFromThis<FEzSalesItem>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> ConsumeActionsValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> AcquireActionsValue;

	public:
        TSharedPtr<FEzSalesItem> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzSalesItem> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSalesItem> WithConsumeActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> ConsumeActions);
        TSharedPtr<FEzSalesItem> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> AcquireActions);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzConsumeAction>>> GetConsumeActions() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzAcquireAction>>> GetAcquireActions() const;

        Gs2::Showcase::Model::FSalesItemPtr ToModel() const;
        static TSharedPtr<FEzSalesItem> FromModel(Gs2::Showcase::Model::FSalesItemPtr Model);
    };
    typedef TSharedPtr<FEzSalesItem> FEzSalesItemPtr;
}