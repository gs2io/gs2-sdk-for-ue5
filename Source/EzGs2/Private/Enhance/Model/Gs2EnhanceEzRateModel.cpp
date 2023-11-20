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

#include "Enhance/Model/Gs2EnhanceEzRateModel.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzRateModel> FEzRateModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithTargetInventoryModelId(
        const TOptional<FString> TargetInventoryModelId
    )
    {
        this->TargetInventoryModelIdValue = TargetInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithAcquireExperienceSuffix(
        const TOptional<FString> AcquireExperienceSuffix
    )
    {
        this->AcquireExperienceSuffixValue = AcquireExperienceSuffix;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithMaterialInventoryModelId(
        const TOptional<FString> MaterialInventoryModelId
    )
    {
        this->MaterialInventoryModelIdValue = MaterialInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithAcquireExperienceHierarchy(
        const TSharedPtr<TArray<FString>> AcquireExperienceHierarchy
    )
    {
        this->AcquireExperienceHierarchyValue = AcquireExperienceHierarchy;
        return SharedThis(this);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }
    TOptional<FString> FEzRateModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRateModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzRateModel::GetTargetInventoryModelId() const
    {
        return TargetInventoryModelIdValue;
    }
    TOptional<FString> FEzRateModel::GetAcquireExperienceSuffix() const
    {
        return AcquireExperienceSuffixValue;
    }
    TOptional<FString> FEzRateModel::GetMaterialInventoryModelId() const
    {
        return MaterialInventoryModelIdValue;
    }
    TSharedPtr<TArray<FString>> FEzRateModel::GetAcquireExperienceHierarchy() const
    {
        return AcquireExperienceHierarchyValue;
    }
    TOptional<FString> FEzRateModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }

    Gs2::Enhance::Model::FRateModelPtr FEzRateModel::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FRateModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTargetInventoryModelId(TargetInventoryModelIdValue)
            ->WithAcquireExperienceSuffix(AcquireExperienceSuffixValue)
            ->WithMaterialInventoryModelId(MaterialInventoryModelIdValue)
            ->WithAcquireExperienceHierarchy(AcquireExperienceHierarchyValue)
            ->WithExperienceModelId(ExperienceModelIdValue);
    }

    TSharedPtr<FEzRateModel> FEzRateModel::FromModel(const Gs2::Enhance::Model::FRateModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRateModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTargetInventoryModelId(Model->GetTargetInventoryModelId())
            ->WithAcquireExperienceSuffix(Model->GetAcquireExperienceSuffix())
            ->WithMaterialInventoryModelId(Model->GetMaterialInventoryModelId())
            ->WithAcquireExperienceHierarchy(Model->GetAcquireExperienceHierarchy())
            ->WithExperienceModelId(Model->GetExperienceModelId());
    }
}