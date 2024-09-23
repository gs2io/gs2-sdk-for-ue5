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

#include "Matchmaking/Model/Gs2MatchmakingUser.h"
#include "Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingRating.h"
#include "Matchmaking/Model/Gs2MatchmakingBallot.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingRating.h"
#include "Matchmaking/Model/Gs2MatchmakingBallot.h"
#include "Core/BpGs2Constant.h"

FGs2MatchmakingGathering UGs2MatchmakingUserFunctionLibrary::Gathering(
    FGs2MatchmakingUser User,
    FString GatheringName
)
{
    FGs2MatchmakingGathering Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::Gathering] User parameter specification is missing."))
        return Return;
    }
    if (GatheringName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::Gathering] GatheringName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Gathering(
        GatheringName
    );
    return Return;
}

FGs2MatchmakingOwnGathering UGs2MatchmakingUserFunctionLibrary::OwnGathering(
    FGs2MatchmakingOwnUser User,
    FString GatheringName
)
{
    FGs2MatchmakingOwnGathering Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnGathering] User parameter specification is missing."))
        return Return;
    }
    if (GatheringName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnGathering] GatheringName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Gathering(
        GatheringName
    );
    return Return;
}

FGs2MatchmakingOwnRating UGs2MatchmakingUserFunctionLibrary::OwnRating(
    FGs2MatchmakingOwnUser User,
    FString RatingName
)
{
    FGs2MatchmakingOwnRating Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnRating] User parameter specification is missing."))
        return Return;
    }
    if (RatingName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnRating] RatingName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Rating(
        RatingName
    );
    return Return;
}

FGs2MatchmakingOwnBallot UGs2MatchmakingUserFunctionLibrary::OwnBallot(
    FGs2MatchmakingOwnUser User,
    FString RatingName,
    FString GatheringName,
    int32 NumberOfPlayer,
    FString KeyId
)
{
    FGs2MatchmakingOwnBallot Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnBallot] User parameter specification is missing."))
        return Return;
    }
    if (RatingName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnBallot] RatingName parameter specification is missing."))
        return Return;
    }
    if (GatheringName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnBallot] GatheringName parameter specification is missing."))
        return Return;
    }
    if (KeyId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingUserFunctionLibrary::OwnBallot] KeyId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Ballot(
        RatingName,
        GatheringName,
        NumberOfPlayer,
        KeyId
    );
    return Return;
}