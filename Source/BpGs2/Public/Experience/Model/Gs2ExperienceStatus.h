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
#include "Experience/Domain/Model/Gs2ExperienceEzStatusGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ExperienceStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExperienceOwnStatus
{
    GENERATED_BODY()

    Gs2::UE5::Experience::Domain::Model::FEzStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ExperienceStatusValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ExperienceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PropertyId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ExperienceValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 RankValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 RankCapValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 NextRankUpExperienceValue = 0;
};

inline FGs2ExperienceStatusValue EzStatusToFGs2ExperienceStatusValue(
    const Gs2::UE5::Experience::Model::FEzStatusPtr Model
)
{
    FGs2ExperienceStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceStatusFunctionLibrary::EzStatusToFGs2ExperienceStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.ExperienceName = Model->GetExperienceName() ? *Model->GetExperienceName() : "";
    Value.PropertyId = Model->GetPropertyId() ? *Model->GetPropertyId() : "";
    Value.ExperienceValue = Model->GetExperienceValue() ? *Model->GetExperienceValue() : 0;
    Value.RankValue = Model->GetRankValue() ? *Model->GetRankValue() : 0;
    Value.RankCapValue = Model->GetRankCapValue() ? *Model->GetRankCapValue() : 0;
    Value.NextRankUpExperienceValue = Model->GetNextRankUpExperienceValue() ? *Model->GetNextRankUpExperienceValue() : 0;
    return Value;
}

inline Gs2::UE5::Experience::Model::FEzStatusPtr FGs2ExperienceStatusValueToEzStatus(
    const FGs2ExperienceStatusValue Model
)
{
    return MakeShared<Gs2::UE5::Experience::Model::FEzStatus>()
        ->WithExperienceName(Model.ExperienceName)
        ->WithPropertyId(Model.PropertyId)
        ->WithExperienceValue(Model.ExperienceValue)
        ->WithRankValue(Model.RankValue)
        ->WithRankCapValue(Model.RankCapValue)
        ->WithNextRankUpExperienceValue(Model.NextRankUpExperienceValue);
}

UCLASS()
class BPGS2_API UGs2ExperienceStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};