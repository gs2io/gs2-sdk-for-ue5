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

#include "Stamina/Model/Gs2StaminaEzStaminaModel.h"

namespace Gs2::UE5::Stamina::Model
{

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithRecoverIntervalMinutes(
        const TOptional<int32> RecoverIntervalMinutes
    )
    {
        this->RecoverIntervalMinutesValue = RecoverIntervalMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithRecoverValue(
        const TOptional<int32> RecoverValue
    )
    {
        this->RecoverValueValue = RecoverValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithInitialCapacity(
        const TOptional<int32> InitialCapacity
    )
    {
        this->InitialCapacityValue = InitialCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithIsOverflow(
        const TOptional<bool> IsOverflow
    )
    {
        this->IsOverflowValue = IsOverflow;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithMaxCapacity(
        const TOptional<int32> MaxCapacity
    )
    {
        this->MaxCapacityValue = MaxCapacity;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithMaxStaminaTable(
        const TSharedPtr<Gs2::UE5::Stamina::Model::FEzMaxStaminaTable> MaxStaminaTable
    )
    {
        this->MaxStaminaTableValue = MaxStaminaTable;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithRecoverIntervalTable(
        const TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverIntervalTable> RecoverIntervalTable
    )
    {
        this->RecoverIntervalTableValue = RecoverIntervalTable;
        return SharedThis(this);
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::WithRecoverValueTable(
        const TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverValueTable> RecoverValueTable
    )
    {
        this->RecoverValueTableValue = RecoverValueTable;
        return SharedThis(this);
    }
    TOptional<FString> FEzStaminaModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzStaminaModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzStaminaModel::GetRecoverIntervalMinutes() const
    {
        return RecoverIntervalMinutesValue;
    }

    FString FEzStaminaModel::GetRecoverIntervalMinutesString() const
    {
        if (!RecoverIntervalMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverIntervalMinutesValue.GetValue());
    }
    TOptional<int32> FEzStaminaModel::GetRecoverValue() const
    {
        return RecoverValueValue;
    }

    FString FEzStaminaModel::GetRecoverValueString() const
    {
        if (!RecoverValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RecoverValueValue.GetValue());
    }
    TOptional<int32> FEzStaminaModel::GetInitialCapacity() const
    {
        return InitialCapacityValue;
    }

    FString FEzStaminaModel::GetInitialCapacityString() const
    {
        if (!InitialCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InitialCapacityValue.GetValue());
    }
    TOptional<bool> FEzStaminaModel::GetIsOverflow() const
    {
        return IsOverflowValue;
    }

    FString FEzStaminaModel::GetIsOverflowString() const
    {
        if (!IsOverflowValue.IsSet())
        {
            return FString("null");
        }
        return FString(IsOverflowValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FEzStaminaModel::GetMaxCapacity() const
    {
        return MaxCapacityValue;
    }

    FString FEzStaminaModel::GetMaxCapacityString() const
    {
        if (!MaxCapacityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxCapacityValue.GetValue());
    }
    TSharedPtr<Gs2::UE5::Stamina::Model::FEzMaxStaminaTable> FEzStaminaModel::GetMaxStaminaTable() const
    {
        return MaxStaminaTableValue;
    }
    TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverIntervalTable> FEzStaminaModel::GetRecoverIntervalTable() const
    {
        return RecoverIntervalTableValue;
    }
    TSharedPtr<Gs2::UE5::Stamina::Model::FEzRecoverValueTable> FEzStaminaModel::GetRecoverValueTable() const
    {
        return RecoverValueTableValue;
    }

    Gs2::Stamina::Model::FStaminaModelPtr FEzStaminaModel::ToModel() const
    {
        return MakeShared<Gs2::Stamina::Model::FStaminaModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithRecoverIntervalMinutes(RecoverIntervalMinutesValue)
            ->WithRecoverValue(RecoverValueValue)
            ->WithInitialCapacity(InitialCapacityValue)
            ->WithIsOverflow(IsOverflowValue)
            ->WithMaxCapacity(MaxCapacityValue)
            ->WithMaxStaminaTable(MaxStaminaTableValue == nullptr ? nullptr : MaxStaminaTableValue->ToModel())
            ->WithRecoverIntervalTable(RecoverIntervalTableValue == nullptr ? nullptr : RecoverIntervalTableValue->ToModel())
            ->WithRecoverValueTable(RecoverValueTableValue == nullptr ? nullptr : RecoverValueTableValue->ToModel());
    }

    TSharedPtr<FEzStaminaModel> FEzStaminaModel::FromModel(const Gs2::Stamina::Model::FStaminaModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStaminaModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithRecoverIntervalMinutes(Model->GetRecoverIntervalMinutes())
            ->WithRecoverValue(Model->GetRecoverValue())
            ->WithInitialCapacity(Model->GetInitialCapacity())
            ->WithIsOverflow(Model->GetIsOverflow())
            ->WithMaxCapacity(Model->GetMaxCapacity())
            ->WithMaxStaminaTable(Model->GetMaxStaminaTable() != nullptr ? Gs2::UE5::Stamina::Model::FEzMaxStaminaTable::FromModel(Model->GetMaxStaminaTable()) : nullptr)
            ->WithRecoverIntervalTable(Model->GetRecoverIntervalTable() != nullptr ? Gs2::UE5::Stamina::Model::FEzRecoverIntervalTable::FromModel(Model->GetRecoverIntervalTable()) : nullptr)
            ->WithRecoverValueTable(Model->GetRecoverValueTable() != nullptr ? Gs2::UE5::Stamina::Model::FEzRecoverValueTable::FromModel(Model->GetRecoverValueTable()) : nullptr);
    }
}