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
#include "Showcase/Model/SalesItemGroup.h"
#include "Gs2ShowcaseEzSalesItem.h"

namespace Gs2::UE5::Showcase::Model
{
	class EZGS2_API FEzSalesItemGroup final : public TSharedFromThis<FEzSalesItemGroup>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem>>> SalesItemsValue;

	public:
        TSharedPtr<FEzSalesItemGroup> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzSalesItemGroup> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSalesItemGroup> WithSalesItems(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem>>> SalesItems);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem>>> GetSalesItems() const;

        Gs2::Showcase::Model::FSalesItemGroupPtr ToModel() const;
        static TSharedPtr<FEzSalesItemGroup> FromModel(Gs2::Showcase::Model::FSalesItemGroupPtr Model);
    };
    typedef TSharedPtr<FEzSalesItemGroup> FEzSalesItemGroupPtr;
}