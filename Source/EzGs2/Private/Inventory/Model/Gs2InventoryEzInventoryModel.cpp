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

#include "Inventory/Model/Gs2InventoryEzInventoryModel.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzInventoryModel> FEzInventoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzInventoryModel> FEzInventoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzInventoryModel> FEzInventoryModel::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FEzInventoryModel> FEzInventoryModel::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }
    TOptional<FString> FEzInventoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzInventoryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzInventoryModel::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FEzInventoryModel::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }
    TOptional<int32> FEzInventoryModel::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FEzInventoryModel::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }

    Gs2::Inventory::Model::FInventoryModelPtr FEzInventoryModel::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FInventoryModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithInitialCapacity(InitialCapacityValue)
            ->WithMaxCapacity(MaxCapacityValue);
    }

    TSharedPtr<FEzInventoryModel> FEzInventoryModel::FromModel(const Gs2::Inventory::Model::FInventoryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzInventoryModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithInitialCapacity(Model->GetInitialCapacity())
            ->WithMaxCapacity(Model->GetMaxCapacity());
    }
}