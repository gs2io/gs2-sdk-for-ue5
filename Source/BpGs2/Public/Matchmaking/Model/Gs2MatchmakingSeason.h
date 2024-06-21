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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonGameSessionDomain.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzSeasonDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingSeason.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingOwnSeason
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingSeason
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzSeasonDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2MatchmakingSeasonFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::SeasonGathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Season|Gathering", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SeasonGathering") FGs2MatchmakingSeasonGathering SeasonGathering(
        FGs2MatchmakingSeason Season,
        int64 Tier,
        FString SeasonGatheringName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::OwnSeasonGathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Season|Gathering", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="OwnSeasonGathering") FGs2MatchmakingOwnSeasonGathering OwnSeasonGathering(
        FGs2MatchmakingOwnSeason Season,
        int64 Tier,
        FString SeasonGatheringName
    );
};