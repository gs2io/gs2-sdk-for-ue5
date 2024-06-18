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
#include "Matchmaking/Model/Gs2MatchmakingSeasonGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingSeason.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingActionDoSeasonMatchmaking.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingDoSeasonMatchmakingSuccessDelegate, FGs2MatchmakingOwnSeasonGathering, SeasonGathering, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingDoSeasonMatchmakingErrorDelegate, FGs2MatchmakingOwnSeasonGathering, SeasonGathering, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingDoSeasonMatchmakingAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnSeason Season;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingDoSeasonMatchmakingSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingDoSeasonMatchmakingErrorDelegate OnError;

    UGs2MatchmakingDoSeasonMatchmakingAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::SeasonGathering::Action::DoSeasonMatchmaking", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Season|SeasonGathering|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingDoSeasonMatchmakingAsyncFunction* DoSeasonMatchmaking(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnSeason Season
    );

    virtual void Activate() override;
};