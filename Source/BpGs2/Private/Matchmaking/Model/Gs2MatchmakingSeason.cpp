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

#include "Matchmaking/Model/Gs2MatchmakingSeason.h"
#include "Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Matchmaking/Model/Gs2MatchmakingSeasonGathering.h"
#include "Core/BpGs2Constant.h"

FGs2MatchmakingSeasonGathering UGs2MatchmakingSeasonFunctionLibrary::SeasonGathering(
    FGs2MatchmakingSeason Season,
    int64 Tier,
    FString SeasonGatheringName
)
{
    FGs2MatchmakingSeasonGathering Return;
    if (Season.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingSaasonUserFunctionLibrary::SeasonGathering] Season parameter specification is missing."))
        return Return;
    }
    if (SeasonGatheringName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingSaasonFunctionLibrary::SeasonGathering] SeasonGatheringName parameter specification is missing."))
        return Return;
    }
    Return.Value = Season.Value->SeasonGathering(
        Tier,
        SeasonGatheringName
    );
    return Return;
}

FGs2MatchmakingOwnSeasonGathering UGs2MatchmakingSeasonFunctionLibrary::OwnSeasonGathering(
    FGs2MatchmakingOwnSeason Season,
    int64 Tier,
    FString SeasonGatheringName
)
{
    FGs2MatchmakingOwnSeasonGathering Return;
    if (Season.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnSeasonGathering] User parameter specification is missing."))
        return Return;
    }
    if (SeasonGatheringName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnSeasonGathering] GatheringName parameter specification is missing."))
        return Return;
    }
    Return.Value = Season.Value->SeasonGathering(
        Tier,
        SeasonGatheringName
    );
    return Return;
}