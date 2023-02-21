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
#include "Showcase/Model/DisplayItem.h"
#include "Gs2ShowcaseEzSalesItem.h"
#include "Gs2ShowcaseEzSalesItemGroup.h"

namespace Gs2::UE5::Showcase::Model
{
	class EZGS2_API FEzDisplayItem final : public TSharedFromThis<FEzDisplayItem>
	{
        TOptional<FString> DisplayItemIdValue;
        TOptional<FString> TypeValue;
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem> SalesItemValue;
        TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItemGroup> SalesItemGroupValue;

	public:
        TSharedPtr<FEzDisplayItem> WithDisplayItemId(const TOptional<FString> DisplayItemId);
        TSharedPtr<FEzDisplayItem> WithType(const TOptional<FString> Type);
        TSharedPtr<FEzDisplayItem> WithSalesItem(const TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem> SalesItem);
        TSharedPtr<FEzDisplayItem> WithSalesItemGroup(const TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItemGroup> SalesItemGroup);

        TOptional<FString> GetDisplayItemId() const;

        TOptional<FString> GetType() const;

        TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItem> GetSalesItem() const;

        TSharedPtr<Gs2::UE5::Showcase::Model::FEzSalesItemGroup> GetSalesItemGroup() const;

        Gs2::Showcase::Model::FDisplayItemPtr ToModel() const;
        static TSharedPtr<FEzDisplayItem> FromModel(Gs2::Showcase::Model::FDisplayItemPtr Model);
    };
    typedef TSharedPtr<FEzDisplayItem> FEzDisplayItemPtr;
}