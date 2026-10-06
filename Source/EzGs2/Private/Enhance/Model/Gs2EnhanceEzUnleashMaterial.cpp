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

#include "Enhance/Model/Gs2EnhanceEzUnleashMaterial.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashMaterial> FEzUnleashMaterial::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashMaterial> FEzUnleashMaterial::WithMaterialType(
        const TOptional<FString> MaterialType
    )
    {
        this->MaterialTypeValue = MaterialType;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashMaterial> FEzUnleashMaterial::WithIndividualSetting(
        const TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSetting> IndividualSetting
    )
    {
        this->IndividualSettingValue = IndividualSetting;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashMaterial> FEzUnleashMaterial::WithQuantitySetting(
        const TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSetting> QuantitySetting
    )
    {
        this->QuantitySettingValue = QuantitySetting;
        return SharedThis(this);
    }
    TOptional<FString> FEzUnleashMaterial::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzUnleashMaterial::GetMaterialType() const
    {
        return MaterialTypeValue;
    }
    TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSetting> FEzUnleashMaterial::GetIndividualSetting() const
    {
        return IndividualSettingValue;
    }
    TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSetting> FEzUnleashMaterial::GetQuantitySetting() const
    {
        return QuantitySettingValue;
    }

    Gs2::Enhance::Model::FUnleashMaterialPtr FEzUnleashMaterial::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashMaterial>()
            ->WithName(NameValue)
            ->WithMaterialType(MaterialTypeValue)
            ->WithIndividualSetting(IndividualSettingValue == nullptr ? nullptr : IndividualSettingValue->ToModel())
            ->WithQuantitySetting(QuantitySettingValue == nullptr ? nullptr : QuantitySettingValue->ToModel());
    }

    TSharedPtr<FEzUnleashMaterial> FEzUnleashMaterial::FromModel(const Gs2::Enhance::Model::FUnleashMaterialPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashMaterial>()
            ->WithName(Model->GetName())
            ->WithMaterialType(Model->GetMaterialType())
            ->WithIndividualSetting(Model->GetIndividualSetting() != nullptr ? Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSetting::FromModel(Model->GetIndividualSetting()) : nullptr)
            ->WithQuantitySetting(Model->GetQuantitySetting() != nullptr ? Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSetting::FromModel(Model->GetQuantitySetting()) : nullptr);
    }
}