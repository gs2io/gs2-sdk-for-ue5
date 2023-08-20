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
#include "Inventory/Model/BigItem.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzBigItem final : public TSharedFromThis<FEzBigItem>
	{
        TOptional<FString> ItemIdValue;
        TOptional<FString> ItemNameValue;
        TOptional<FString> CountValue;

	public:
        TSharedPtr<FEzBigItem> WithItemId(const TOptional<FString> ItemId);
        TSharedPtr<FEzBigItem> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FEzBigItem> WithCount(const TOptional<FString> Count);

        TOptional<FString> GetItemId() const;

        TOptional<FString> GetItemName() const;

        TOptional<FString> GetCount() const;

        Gs2::Inventory::Model::FBigItemPtr ToModel() const;
        static TSharedPtr<FEzBigItem> FromModel(Gs2::Inventory::Model::FBigItemPtr Model);
    };
    typedef TSharedPtr<FEzBigItem> FEzBigItemPtr;
}