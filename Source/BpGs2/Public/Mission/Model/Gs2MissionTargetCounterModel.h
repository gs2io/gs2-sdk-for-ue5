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

#include "Mission/Model/Gs2MissionEzTargetCounterModel.h"
#include "Gs2MissionTargetCounterModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionTargetCounterModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString CounterName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ScopeType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ResetType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ConditionName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 Value = 0;
};

inline FGs2MissionTargetCounterModel EzTargetCounterModelToFGs2MissionTargetCounterModel(
    const Gs2::UE5::Mission::Model::FEzTargetCounterModelPtr Model
)
{
    FGs2MissionTargetCounterModel Value;
    Value.CounterName = Model->GetCounterName() ? *Model->GetCounterName() : "";
    Value.ScopeType = Model->GetScopeType() ? *Model->GetScopeType() : "";
    Value.ResetType = Model->GetResetType() ? *Model->GetResetType() : "";
    Value.ConditionName = Model->GetConditionName() ? *Model->GetConditionName() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : 0;
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzTargetCounterModelPtr FGs2MissionTargetCounterModelToEzTargetCounterModel(
    const FGs2MissionTargetCounterModel Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzTargetCounterModel>()
        ->WithCounterName(Model.CounterName)
        ->WithScopeType(Model.ScopeType)
        ->WithResetType(Model.ResetType)
        ->WithConditionName(Model.ConditionName)
        ->WithValue(Model.Value);
}