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

#include "EzGs2/Public/Inventory/Model/Gs2InventoryEzInventory.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzInventory> FEzInventory::WithInventoryId(
        const TOptional<FString> InventoryId
    )
    {
        this->InventoryIdValue = InventoryId;
        return SharedThis(this);
    }

    TSharedPtr<FEzInventory> FEzInventory::WithInventoryName(
        const TOptional<FString> InventoryName
    )
    {
        this->InventoryNameValue = InventoryName;
        return SharedThis(this);
    }

    TSharedPtr<FEzInventory> FEzInventory::WithCurrentInventoryCapacityUsage(
        const TOptional<int32> CurrentInventoryCapacityUsage
    )
    {
        this->CurrentInventoryCapacityUsageValue = CurrentInventoryCapacityUsage;
        return SharedThis(this);
    }

    TSharedPtr<FEzInventory> FEzInventory::WithCurrentInventoryMaxCapacity(
        const TOptional<int32> CurrentInventoryMaxCapacity
    )
    {
        this->CurrentInventoryMaxCapacityValue = CurrentInventoryMaxCapacity;
        return SharedThis(this);
    }
    TOptional<FString> FEzInventory::GetInventoryId() const
    {
        return InventoryIdValue;
    }
    TOptional<FString> FEzInventory::GetInventoryName() const
    {
        return InventoryNameValue;
    }
    TOptional<int32> FEzInventory::GetCurrentInventoryCapacityUsage() const
    {
        return CurrentInventoryCapacityUsageValue;
    }

    FString FEzInventory::GetCurrentInventoryCapacityUsageString() const
    {
        if (!CurrentInventoryCapacityUsageValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentInventoryCapacityUsageValue.GetValue());
    }
    TOptional<int32> FEzInventory::GetCurrentInventoryMaxCapacity() const
    {
        return CurrentInventoryMaxCapacityValue;
    }

    FString FEzInventory::GetCurrentInventoryMaxCapacityString() const
    {
        if (!CurrentInventoryMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentInventoryMaxCapacityValue.GetValue());
    }

    Gs2::Inventory::Model::FInventoryPtr FEzInventory::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FInventory>()
            ->WithInventoryId(InventoryIdValue)
            ->WithInventoryName(InventoryNameValue)
            ->WithCurrentInventoryCapacityUsage(CurrentInventoryCapacityUsageValue)
            ->WithCurrentInventoryMaxCapacity(CurrentInventoryMaxCapacityValue);
    }

    TSharedPtr<FEzInventory> FEzInventory::FromModel(const Gs2::Inventory::Model::FInventoryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzInventory>()
            ->WithInventoryId(Model->GetInventoryId())
            ->WithInventoryName(Model->GetInventoryName())
            ->WithCurrentInventoryCapacityUsage(Model->GetCurrentInventoryCapacityUsage())
            ->WithCurrentInventoryMaxCapacity(Model->GetCurrentInventoryMaxCapacity());
    }
}