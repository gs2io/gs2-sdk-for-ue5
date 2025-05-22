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

#include "Mission/Model/Gs2MissionEzScopedValue.h"
#include "Gs2MissionScopedValue.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionScopedValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ResetType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ConditionName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 Value = 0;
};

inline FGs2MissionScopedValue EzScopedValueToFGs2MissionScopedValue(
    const Gs2::UE5::Mission::Model::FEzScopedValuePtr Model
)
{
    FGs2MissionScopedValue Value;
    Value.ResetType = Model->GetResetType() ? *Model->GetResetType() : "";
    Value.ConditionName = Model->GetConditionName() ? *Model->GetConditionName() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : 0;
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzScopedValuePtr FGs2MissionScopedValueToEzScopedValue(
    const FGs2MissionScopedValue Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzScopedValue>()
        ->WithResetType(Model.ResetType)
        ->WithConditionName(Model.ConditionName)
        ->WithValue(Model.Value);
}