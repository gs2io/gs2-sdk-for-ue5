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

#include "Inventory/Model/Gs2InventoryEzSimpleInventoryModel.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzSimpleInventoryModel> FEzSimpleInventoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSimpleInventoryModel> FEzSimpleInventoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FEzSimpleInventoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSimpleInventoryModel::GetMetadata() const
    {
        return MetadataValue;
    }

    Gs2::Inventory::Model::FSimpleInventoryModelPtr FEzSimpleInventoryModel::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FSimpleInventoryModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue);
    }

    TSharedPtr<FEzSimpleInventoryModel> FEzSimpleInventoryModel::FromModel(const Gs2::Inventory::Model::FSimpleInventoryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSimpleInventoryModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata());
    }
}