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

#include "Enhance/Model/Gs2EnhanceEzUnleashIndividualMaterialSetting.h"
#include "Gs2EnhanceUnleashIndividualMaterialSetting.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashIndividualMaterialSetting
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString MatchType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString GradeCondition = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 GradeValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Count = 0;
};

inline FGs2EnhanceUnleashIndividualMaterialSetting EzUnleashIndividualMaterialSettingToFGs2EnhanceUnleashIndividualMaterialSetting(
    const Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSettingPtr Model
)
{
    FGs2EnhanceUnleashIndividualMaterialSetting Value;
    Value.MatchType = Model->GetMatchType() ? *Model->GetMatchType() : "";
    Value.GradeCondition = Model->GetGradeCondition() ? *Model->GetGradeCondition() : "";
    Value.GradeValue = Model->GetGradeValue() ? *Model->GetGradeValue() : 0;
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSettingPtr FGs2EnhanceUnleashIndividualMaterialSettingToEzUnleashIndividualMaterialSetting(
    const FGs2EnhanceUnleashIndividualMaterialSetting Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzUnleashIndividualMaterialSetting>()
        ->WithMatchType(Model.MatchType)
        ->WithGradeCondition(Model.GradeCondition)
        ->WithGradeValue(Model.GradeValue)
        ->WithCount(Model.Count);
}