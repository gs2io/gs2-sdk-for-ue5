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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzUserGameSessionDomain.h"
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzUserDomain.h"
#include "Gs2MatchmakingUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingUser
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzUserDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2MatchmakingUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Gathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Gathering", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Gathering") FGs2MatchmakingGathering Gathering(
        FGs2MatchmakingUser User,
        FString GatheringName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::OwnGathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Gathering", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Gathering") FGs2MatchmakingOwnGathering OwnGathering(
        FGs2MatchmakingOwnUser User,
        FString GatheringName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::OwnBallot", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Ballot", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Ballot") FGs2MatchmakingOwnBallot OwnBallot(
        FGs2MatchmakingOwnUser User,
        FString RatingName,
        FString GatheringName,
        int32 NumberOfPlayer,
        FString KeyId
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::OwnRating", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Rating", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Rating") FGs2MatchmakingOwnRating OwnRating(
        FGs2MatchmakingOwnUser User,
        FString RatingName
    );
};