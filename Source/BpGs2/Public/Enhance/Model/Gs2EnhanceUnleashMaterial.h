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

#include "Enhance/Model/Gs2EnhanceEzUnleashMaterial.h"
#include "Enhance/Model/Gs2EnhanceUnleashIndividualMaterialSetting.h"
#include "Enhance/Model/Gs2EnhanceUnleashQuantityMaterialSetting.h"
#include "Gs2EnhanceUnleashMaterial.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashMaterial
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString MaterialType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FGs2EnhanceUnleashIndividualMaterialSetting IndividualSetting = FGs2EnhanceUnleashIndividualMaterialSetting();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FGs2EnhanceUnleashQuantityMaterialSetting QuantitySetting = FGs2EnhanceUnleashQuantityMaterialSetting();
};

inline FGs2EnhanceUnleashMaterial EzUnleashMaterialToFGs2EnhanceUnleashMaterial(
    const Gs2::UE5::Enhance::Model::FEzUnleashMaterialPtr Model
)
{
    FGs2EnhanceUnleashMaterial Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.MaterialType = Model->GetMaterialType() ? *Model->GetMaterialType() : "";
    Value.IndividualSetting = Model->GetIndividualSetting() ? EzUnleashIndividualMaterialSettingToFGs2EnhanceUnleashIndividualMaterialSetting(Model->GetIndividualSetting()) : FGs2EnhanceUnleashIndividualMaterialSetting();
    Value.QuantitySetting = Model->GetQuantitySetting() ? EzUnleashQuantityMaterialSettingToFGs2EnhanceUnleashQuantityMaterialSetting(Model->GetQuantitySetting()) : FGs2EnhanceUnleashQuantityMaterialSetting();
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzUnleashMaterialPtr FGs2EnhanceUnleashMaterialToEzUnleashMaterial(
    const FGs2EnhanceUnleashMaterial Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzUnleashMaterial>()
        ->WithName(Model.Name)
        ->WithMaterialType(Model.MaterialType)
        ->WithIndividualSetting(FGs2EnhanceUnleashIndividualMaterialSettingToEzUnleashIndividualMaterialSetting(Model.IndividualSetting))
        ->WithQuantitySetting(FGs2EnhanceUnleashQuantityMaterialSettingToEzUnleashQuantityMaterialSetting(Model.QuantitySetting));
}