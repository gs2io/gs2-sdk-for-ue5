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

#include "Schedule/Model/Gs2ScheduleEzRepeatSchedule.h"
#include "Gs2ScheduleRepeatSchedule.generated.h"

USTRUCT(BlueprintType)
struct FGs2ScheduleRepeatSchedule
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 RepeatCount = 0;
    UPROPERTY(BlueprintReadWrite)
    int64 CurrentRepeatStartAt = 0;
    UPROPERTY(BlueprintReadWrite)
    int64 CurrentRepeatEndAt = 0;
    UPROPERTY(BlueprintReadWrite)
    int64 LastRepeatEndAt = 0;
    UPROPERTY(BlueprintReadWrite)
    int64 NextRepeatStartAt = 0;
};

inline FGs2ScheduleRepeatSchedule EzRepeatScheduleToFGs2ScheduleRepeatSchedule(
    const Gs2::UE5::Schedule::Model::FEzRepeatSchedulePtr Model
)
{
    FGs2ScheduleRepeatSchedule Value;
    Value.RepeatCount = Model->GetRepeatCount() ? *Model->GetRepeatCount() : 0;
    Value.CurrentRepeatStartAt = Model->GetCurrentRepeatStartAt() ? *Model->GetCurrentRepeatStartAt() : 0;
    Value.CurrentRepeatEndAt = Model->GetCurrentRepeatEndAt() ? *Model->GetCurrentRepeatEndAt() : 0;
    Value.LastRepeatEndAt = Model->GetLastRepeatEndAt() ? *Model->GetLastRepeatEndAt() : 0;
    Value.NextRepeatStartAt = Model->GetNextRepeatStartAt() ? *Model->GetNextRepeatStartAt() : 0;
    return Value;
}

inline Gs2::UE5::Schedule::Model::FEzRepeatSchedulePtr FGs2ScheduleRepeatScheduleToEzRepeatSchedule(
    const FGs2ScheduleRepeatSchedule Model
)
{
    return MakeShared<Gs2::UE5::Schedule::Model::FEzRepeatSchedule>()
        ->WithRepeatCount(Model.RepeatCount)
        ->WithCurrentRepeatStartAt(Model.CurrentRepeatStartAt)
        ->WithCurrentRepeatEndAt(Model.CurrentRepeatEndAt)
        ->WithLastRepeatEndAt(Model.LastRepeatEndAt)
        ->WithNextRepeatStartAt(Model.NextRepeatStartAt);
}