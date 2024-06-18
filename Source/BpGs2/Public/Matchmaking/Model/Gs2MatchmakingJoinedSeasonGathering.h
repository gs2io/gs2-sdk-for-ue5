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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzJoinedSeasonGatheringGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingJoinedSeasonGathering.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingOwnJoinedSeasonGathering
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzJoinedSeasonGatheringGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingJoinedSeasonGatheringValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString SeasonName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Season = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Tier = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString SeasonGatheringName = "";
};

inline FGs2MatchmakingJoinedSeasonGatheringValue EzJoinedSeasonGatheringToFGs2MatchmakingJoinedSeasonGatheringValue(
    const Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGatheringPtr Model
)
{
    FGs2MatchmakingJoinedSeasonGatheringValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingJoinedSeasonGatheringFunctionLibrary::EzJoinedSeasonGatheringToFGs2MatchmakingJoinedSeasonGatheringValue] Model parameter specification is missing."))
        return Value;
    }
    Value.SeasonName = Model->GetSeasonName() ? *Model->GetSeasonName() : "";
    Value.Season = Model->GetSeason() ? *Model->GetSeason() : 0;
    Value.Tier = Model->GetTier() ? *Model->GetTier() : 0;
    Value.SeasonGatheringName = Model->GetSeasonGatheringName() ? *Model->GetSeasonGatheringName() : "";
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGatheringPtr FGs2MatchmakingJoinedSeasonGatheringValueToEzJoinedSeasonGathering(
    const FGs2MatchmakingJoinedSeasonGatheringValue Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGathering>()
        ->WithSeasonName(Model.SeasonName)
        ->WithSeason(Model.Season)
        ->WithTier(Model.Tier)
        ->WithSeasonGatheringName(Model.SeasonGatheringName);
}

UCLASS()
class BPGS2_API UGs2MatchmakingJoinedSeasonGatheringFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};