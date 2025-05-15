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
#include "Showcase/Model/Showcase.h"
#include "Gs2ShowcaseEzDisplayItem.h"

namespace Gs2::UE5::Showcase::Model
{
	class EZGS2_API FEzShowcase final : public TSharedFromThis<FEzShowcase>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItem>>> DisplayItemsValue;
        TOptional<FString> SalesPeriodEventIdValue;

	public:
        TSharedPtr<FEzShowcase> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzShowcase> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzShowcase> WithDisplayItems(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItem>>> DisplayItems);
        TSharedPtr<FEzShowcase> WithSalesPeriodEventId(const TOptional<FString> SalesPeriodEventId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzDisplayItem>>> GetDisplayItems() const;

        TOptional<FString> GetSalesPeriodEventId() const;

        Gs2::Showcase::Model::FShowcasePtr ToModel() const;
        static TSharedPtr<FEzShowcase> FromModel(Gs2::Showcase::Model::FShowcasePtr Model);
    };
    typedef TSharedPtr<FEzShowcase> FEzShowcasePtr;
}