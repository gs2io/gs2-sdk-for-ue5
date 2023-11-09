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

#include "Matchmaking/Model/Gs2MatchmakingEzGameResult.h"
#include "Gs2MatchmakingGameResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingGameResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Rank = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
};

inline FGs2MatchmakingGameResult EzGameResultToFGs2MatchmakingGameResult(
    const Gs2::UE5::Matchmaking::Model::FEzGameResultPtr Model
)
{
    FGs2MatchmakingGameResult Value;
    Value.Rank = Model->GetRank() ? *Model->GetRank() : 0;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzGameResultPtr FGs2MatchmakingGameResultToEzGameResult(
    const FGs2MatchmakingGameResult Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzGameResult>()
        ->WithRank(Model.Rank)
        ->WithUserId(Model.UserId);
}