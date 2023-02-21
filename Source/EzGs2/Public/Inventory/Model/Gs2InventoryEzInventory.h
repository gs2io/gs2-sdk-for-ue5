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
#include "Inventory/Model/Inventory.h"

namespace Gs2::UE5::Inventory::Model
{
	class EZGS2_API FEzInventory final : public TSharedFromThis<FEzInventory>
	{
        TOptional<FString> InventoryIdValue;
        TOptional<FString> InventoryNameValue;
        TOptional<int32> CurrentInventoryCapacityUsageValue;
        TOptional<int32> CurrentInventoryMaxCapacityValue;

	public:
        TSharedPtr<FEzInventory> WithInventoryId(const TOptional<FString> InventoryId);
        TSharedPtr<FEzInventory> WithInventoryName(const TOptional<FString> InventoryName);
        TSharedPtr<FEzInventory> WithCurrentInventoryCapacityUsage(const TOptional<int32> CurrentInventoryCapacityUsage);
        TSharedPtr<FEzInventory> WithCurrentInventoryMaxCapacity(const TOptional<int32> CurrentInventoryMaxCapacity);

        TOptional<FString> GetInventoryId() const;

        TOptional<FString> GetInventoryName() const;

        TOptional<int32> GetCurrentInventoryCapacityUsage() const;
        FString GetCurrentInventoryCapacityUsageString() const;

        TOptional<int32> GetCurrentInventoryMaxCapacity() const;
        FString GetCurrentInventoryMaxCapacityString() const;

        Gs2::Inventory::Model::FInventoryPtr ToModel() const;
        static TSharedPtr<FEzInventory> FromModel(Gs2::Inventory::Model::FInventoryPtr Model);
    };
    typedef TSharedPtr<FEzInventory> FEzInventoryPtr;
}