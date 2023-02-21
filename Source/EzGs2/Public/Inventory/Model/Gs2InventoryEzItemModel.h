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
#include "Inventory/Model/ItemModel.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzItemModel final : public TSharedFromThis<FEzItemModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> StackingLimitValue;
        TOptional<bool> AllowMultipleStacksValue;
        TOptional<int32> SortValueValue;

	public:
        TSharedPtr<FEzItemModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzItemModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzItemModel> WithStackingLimit(const TOptional<int64> StackingLimit);
        TSharedPtr<FEzItemModel> WithAllowMultipleStacks(const TOptional<bool> AllowMultipleStacks);
        TSharedPtr<FEzItemModel> WithSortValue(const TOptional<int32> SortValue);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetStackingLimit() const;
        FString GetStackingLimitString() const;

        TOptional<bool> GetAllowMultipleStacks() const;
        FString GetAllowMultipleStacksString() const;

        TOptional<int32> GetSortValue() const;
        FString GetSortValueString() const;

        Gs2::Inventory::Model::FItemModelPtr ToModel() const;
        static TSharedPtr<FEzItemModel> FromModel(Gs2::Inventory::Model::FItemModelPtr Model);
    };
    typedef TSharedPtr<FEzItemModel> FEzItemModelPtr;
}