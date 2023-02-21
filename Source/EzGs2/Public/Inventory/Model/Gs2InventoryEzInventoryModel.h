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
#include "Inventory/Model/InventoryModel.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzInventoryModel final : public TSharedFromThis<FEzInventoryModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialCapacityValue;
        TOptional<int32> MaxCapacityValue;

	public:
        TSharedPtr<FEzInventoryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzInventoryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzInventoryModel> WithInitialCapacity(const TOptional<int32> InitialCapacity);
        TSharedPtr<FEzInventoryModel> WithMaxCapacity(const TOptional<int32> MaxCapacity);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int32> GetInitialCapacity() const;
        FString GetInitialCapacityString() const;

        TOptional<int32> GetMaxCapacity() const;
        FString GetMaxCapacityString() const;

        Gs2::Inventory::Model::FInventoryModelPtr ToModel() const;
        static TSharedPtr<FEzInventoryModel> FromModel(Gs2::Inventory::Model::FInventoryModelPtr Model);
    };
    typedef TSharedPtr<FEzInventoryModel> FEzInventoryModelPtr;
}