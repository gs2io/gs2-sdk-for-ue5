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

#include "Matchmaking/Model/Gs2MatchmakingEzTimeSpan.h"
#include "Gs2MatchmakingTimeSpan.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingTimeSpan
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    int32 Days = 0;
    UPROPERTY(BlueprintReadWrite)
    int32 Hours = 0;
    UPROPERTY(BlueprintReadWrite)
    int32 Minutes = 0;
};

inline FGs2MatchmakingTimeSpan EzTimeSpanToFGs2MatchmakingTimeSpan(
    const Gs2::UE5::Matchmaking::Model::FEzTimeSpanPtr Model
)
{
    FGs2MatchmakingTimeSpan Value;
    Value.Days = Model->GetDays() ? *Model->GetDays() : 0;
    Value.Hours = Model->GetHours() ? *Model->GetHours() : 0;
    Value.Minutes = Model->GetMinutes() ? *Model->GetMinutes() : 0;
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzTimeSpanPtr FGs2MatchmakingTimeSpanToEzTimeSpan(
    const FGs2MatchmakingTimeSpan Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzTimeSpan>()
        ->WithDays(Model.Days)
        ->WithHours(Model.Hours)
        ->WithMinutes(Model.Minutes);
}