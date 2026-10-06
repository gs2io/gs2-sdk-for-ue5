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

#pragma once

#include "CoreMinimal.h"
#include "Enhance/Model/UnleashMaterial.h"
#include "Gs2EnhanceEzUnleashIndividualMaterialSetting.h"
#include "Gs2EnhanceEzUnleashQuantityMaterialSetting.h"

namespace Gs2::UE5::Enhance::Model
{
	class EZGS2_API FEzUnleashMaterial final : public TSharedFromThis<FEzUnleashMaterial>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MaterialTypeValue;
        TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSetting> IndividualSettingValue;
        TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSetting> QuantitySettingValue;

	public:
        TSharedPtr<FEzUnleashMaterial> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzUnleashMaterial> WithMaterialType(const TOptional<FString> MaterialType);
        TSharedPtr<FEzUnleashMaterial> WithIndividualSetting(const TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSetting> IndividualSetting);
        TSharedPtr<FEzUnleashMaterial> WithQuantitySetting(const TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSetting> QuantitySetting);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMaterialType() const;

        TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSetting> GetIndividualSetting() const;

        TSharedPtr<Gs2::UE5::Enhance::Model::FEzUnleashQuantityMaterialSetting> GetQuantitySetting() const;

        Gs2::Enhance::Model::FUnleashMaterialPtr ToModel() const;
        static TSharedPtr<FEzUnleashMaterial> FromModel(Gs2::Enhance::Model::FUnleashMaterialPtr Model);
    };
    typedef TSharedPtr<FEzUnleashMaterial> FEzUnleashMaterialPtr;
}