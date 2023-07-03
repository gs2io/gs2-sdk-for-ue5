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
#include "Inventory/Model/ItemSet.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzItemSet final : public TSharedFromThis<FEzItemSet>
	{
        TOptional<FString> ItemSetIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> InventoryNameValue;
        TOptional<FString> ItemNameValue;
        TOptional<int64> CountValue;
        TOptional<int32> SortValueValue;
        TOptional<int64> ExpiresAtValue;
        TSharedPtr<TArray<FString>> ReferenceOfValue;

	public:
        TSharedPtr<FEzItemSet> WithItemSetId(const TOptional<FString> ItemSetId);
        TSharedPtr<FEzItemSet> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzItemSet> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FEzItemSet> WithItemName(const TOptional<FString> ItemName);
        TSharedPtr<FEzItemSet> WithCount(const TOptional<int64> Count);
        TSharedPtr<FEzItemSet> WithSortValue(const TOptional<int32> SortValue);
        TSharedPtr<FEzItemSet> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FEzItemSet> WithReferenceOf(const TSharedPtr<TArray<FString>> ReferenceOf);

        TOptional<FString> GetItemSetId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetInventoryName() const;

        TOptional<FString> GetItemName() const;

        TOptional<int64> GetCount() const;
        FString GetCountString() const;

        TOptional<int32> GetSortValue() const;
        FString GetSortValueString() const;

        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        TSharedPtr<TArray<FString>> GetReferenceOf() const;

        Gs2::Inventory::Model::FItemSetPtr ToModel() const;
        static TSharedPtr<FEzItemSet> FromModel(Gs2::Inventory::Model::FItemSetPtr Model);
    };
    typedef TSharedPtr<FEzItemSet> FEzItemSetPtr;
}