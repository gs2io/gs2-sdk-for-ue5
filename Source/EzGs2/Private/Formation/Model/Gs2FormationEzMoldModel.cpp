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

#include "EzGs2/Public/Formation/Model/Gs2FormationEzMoldModel.h"

namespace Gs2::UE5::Formation::Model
{

    TSharedPtr<FEzMoldModel> FEzMoldModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzMoldModel> FEzMoldModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzMoldModel> FEzMoldModel::WithFormModel(
        const TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModel> FormModel
    )
    {
        this->FormModelValue = FormModel;
        return SharedThis(this);
    }

    TSharedPtr<FEzMoldModel> FEzMoldModel::WithInitialMaxCapacity(
        const TOptional<int32> InitialMaxCapacity
    )
    {
        this->InitialMaxCapacityValue = InitialMaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FEzMoldModel> FEzMoldModel::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }
    TOptional<FString> FEzMoldModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzMoldModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<Gs2::UE5::Formation::Model::FEzFormModel> FEzMoldModel::GetFormModel() const
    {
        return FormModelValue;
    }
    TOptional<int32> FEzMoldModel::GetInitialMaxCapacity() const
    {
        return InitialMaxCapacityValue;
    }

    FString FEzMoldModel::GetInitialMaxCapacityString() const
    {
        if (!InitialMaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), InitialMaxCapacityValue.GetValue());
    }
    TOptional<int32> FEzMoldModel::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FEzMoldModel::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), MaxCapacityValue.GetValue());
    }

    Gs2::Formation::Model::FMoldModelPtr FEzMoldModel::ToModel() const
    {
        return MakeShared<Gs2::Formation::Model::FMoldModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithFormModel(FormModelValue == nullptr ? nullptr : FormModelValue->ToModel())
            ->WithInitialMaxCapacity(InitialMaxCapacityValue)
            ->WithMaxCapacity(MaxCapacityValue);
    }

    TSharedPtr<FEzMoldModel> FEzMoldModel::FromModel(const Gs2::Formation::Model::FMoldModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMoldModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithFormModel(Model->GetFormModel() != nullptr ? Gs2::UE5::Formation::Model::FEzFormModel::FromModel(Model->GetFormModel()) : nullptr)
            ->WithInitialMaxCapacity(Model->GetInitialMaxCapacity())
            ->WithMaxCapacity(Model->GetMaxCapacity());
    }
}