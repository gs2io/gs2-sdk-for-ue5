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
#include "Matchmaking/Model/Gs2MatchmakingJoinedSeasonGathering.h"
#include "Matchmaking/Model/Gs2MatchmakingJoinedSeasonGathering.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingJoinedSeasonGatheringGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingJoinedSeasonGatheringGetValueSuccessDelegate, FGs2MatchmakingJoinedSeasonGatheringValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingJoinedSeasonGatheringGetValueErrorDelegate, FGs2MatchmakingJoinedSeasonGatheringValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingJoinedSeasonGatheringGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnJoinedSeasonGathering JoinedSeasonGathering;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingJoinedSeasonGatheringGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingJoinedSeasonGatheringGetValueErrorDelegate OnError;

    UGs2MatchmakingJoinedSeasonGatheringGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Fetch::GetValueOfJoinedSeasonGathering", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Season|JoinedSeasonGathering|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingJoinedSeasonGatheringGetValueAsyncFunction* JoinedSeasonGatheringGetValue(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnJoinedSeasonGathering JoinedSeasonGathering
    );

    virtual void Activate() override;
};