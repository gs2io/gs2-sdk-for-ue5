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

#include "EzGs2/Public/Stamina/Model/Gs2StaminaEzMaxStaminaTable.h"

namespace Gs2::UE5::Stamina::Model
{

    TSharedPtr<FEzMaxStaminaTable> FEzMaxStaminaTable::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzMaxStaminaTable> FEzMaxStaminaTable::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzMaxStaminaTable> FEzMaxStaminaTable::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzMaxStaminaTable> FEzMaxStaminaTable::WithValues(
        const TSharedPtr<TArray<int32>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }
    TOptional<FString> FEzMaxStaminaTable::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzMaxStaminaTable::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzMaxStaminaTable::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TSharedPtr<TArray<int32>> FEzMaxStaminaTable::GetValues() const
    {
        return ValuesValue;
    }

    Gs2::Stamina::Model::FMaxStaminaTablePtr FEzMaxStaminaTable::ToModel() const
    {
        return MakeShared<Gs2::Stamina::Model::FMaxStaminaTable>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithExperienceModelId(ExperienceModelIdValue)
            ->WithValues(ValuesValue);
    }

    TSharedPtr<FEzMaxStaminaTable> FEzMaxStaminaTable::FromModel(const Gs2::Stamina::Model::FMaxStaminaTablePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMaxStaminaTable>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithExperienceModelId(Model->GetExperienceModelId())
            ->WithValues(Model->GetValues());
    }
}