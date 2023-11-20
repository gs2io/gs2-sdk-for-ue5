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

#include "Enchant/Model/Gs2EnchantEzRarityParameterValueModel.h"

namespace Gs2::UE5::Enchant::Model
{

    TSharedPtr<FEzRarityParameterValueModel> FEzRarityParameterValueModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterValueModel> FEzRarityParameterValueModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterValueModel> FEzRarityParameterValueModel::WithResourceName(
        const TOptional<FString> ResourceName
    )
    {
        this->ResourceNameValue = ResourceName;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterValueModel> FEzRarityParameterValueModel::WithResourceValue(
        const TOptional<int64> ResourceValue
    )
    {
        this->ResourceValueValue = ResourceValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzRarityParameterValueModel> FEzRarityParameterValueModel::WithWeight(
        const TOptional<int32> Weight
    )
    {
        this->WeightValue = Weight;
        return SharedThis(this);
    }
    TOptional<FString> FEzRarityParameterValueModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRarityParameterValueModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzRarityParameterValueModel::GetResourceName() const
    {
        return ResourceNameValue;
    }
    TOptional<int64> FEzRarityParameterValueModel::GetResourceValue() const
    {
        return ResourceValueValue;
    }

    FString FEzRarityParameterValueModel::GetResourceValueString() const
    {
        if (!ResourceValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ResourceValueValue.GetValue());
    }
    TOptional<int32> FEzRarityParameterValueModel::GetWeight() const
    {
        return WeightValue;
    }

    FString FEzRarityParameterValueModel::GetWeightString() const
    {
        if (!WeightValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), WeightValue.GetValue());
    }

    Gs2::Enchant::Model::FRarityParameterValueModelPtr FEzRarityParameterValueModel::ToModel() const
    {
        return MakeShared<Gs2::Enchant::Model::FRarityParameterValueModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithResourceName(ResourceNameValue)
            ->WithResourceValue(ResourceValueValue)
            ->WithWeight(WeightValue);
    }

    TSharedPtr<FEzRarityParameterValueModel> FEzRarityParameterValueModel::FromModel(const Gs2::Enchant::Model::FRarityParameterValueModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRarityParameterValueModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithResourceName(Model->GetResourceName())
            ->WithResourceValue(Model->GetResourceValue())
            ->WithWeight(Model->GetWeight());
    }
}