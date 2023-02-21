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

#include "EzGs2/Public/Stamina/Model/Gs2StaminaEzRecoverValueTable.h"

namespace Gs2::UE5::Stamina::Model
{

    TSharedPtr<FEzRecoverValueTable> FEzRecoverValueTable::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRecoverValueTable> FEzRecoverValueTable::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRecoverValueTable> FEzRecoverValueTable::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzRecoverValueTable> FEzRecoverValueTable::WithValues(
        const TSharedPtr<TArray<int32>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }
    TOptional<FString> FEzRecoverValueTable::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRecoverValueTable::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzRecoverValueTable::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TSharedPtr<TArray<int32>> FEzRecoverValueTable::GetValues() const
    {
        return ValuesValue;
    }

    Gs2::Stamina::Model::FRecoverValueTablePtr FEzRecoverValueTable::ToModel() const
    {
        return MakeShared<Gs2::Stamina::Model::FRecoverValueTable>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithExperienceModelId(ExperienceModelIdValue)
            ->WithValues(ValuesValue);
    }

    TSharedPtr<FEzRecoverValueTable> FEzRecoverValueTable::FromModel(const Gs2::Stamina::Model::FRecoverValueTablePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRecoverValueTable>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithExperienceModelId(Model->GetExperienceModelId())
            ->WithValues(Model->GetValues());
    }
}