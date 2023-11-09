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
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingGathering.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingPlayer.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingActionDoMatchmaking.generated.h"
  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingDoMatchmakingSuccessDelegate, FGs2MatchmakingGatheringValue, Gathering, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingDoMatchmakingErrorDelegate, FGs2MatchmakingGatheringValue, Gathering, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingDoMatchmakingAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnUser User;
    FGs2MatchmakingPlayer Player;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingDoMatchmakingSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingDoMatchmakingErrorDelegate OnError;

    UGs2MatchmakingDoMatchmakingAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Gathering::Action::DoMatchmaking", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Gathering|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingDoMatchmakingAsyncFunction* DoMatchmaking(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnUser User,
        FGs2MatchmakingPlayer Player
    );

    virtual void Activate() override;
};