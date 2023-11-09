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

#include "Mission/Model/Gs2MissionEzCounterScopeModel.h"
#include "Gs2MissionCounterScopeModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionCounterScopeModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ResetType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 ResetDayOfMonth = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ResetDayOfWeek = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 ResetHour = 0;
};

inline FGs2MissionCounterScopeModel EzCounterScopeModelToFGs2MissionCounterScopeModel(
    const Gs2::UE5::Mission::Model::FEzCounterScopeModelPtr Model
)
{
    FGs2MissionCounterScopeModel Value;
    Value.ResetType = Model->GetResetType() ? *Model->GetResetType() : "";
    Value.ResetDayOfMonth = Model->GetResetDayOfMonth() ? *Model->GetResetDayOfMonth() : 0;
    Value.ResetDayOfWeek = Model->GetResetDayOfWeek() ? *Model->GetResetDayOfWeek() : "";
    Value.ResetHour = Model->GetResetHour() ? *Model->GetResetHour() : 0;
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzCounterScopeModelPtr FGs2MissionCounterScopeModelToEzCounterScopeModel(
    const FGs2MissionCounterScopeModel Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzCounterScopeModel>()
        ->WithResetType(Model.ResetType)
        ->WithResetDayOfMonth(Model.ResetDayOfMonth)
        ->WithResetDayOfWeek(Model.ResetDayOfWeek)
        ->WithResetHour(Model.ResetHour);
}