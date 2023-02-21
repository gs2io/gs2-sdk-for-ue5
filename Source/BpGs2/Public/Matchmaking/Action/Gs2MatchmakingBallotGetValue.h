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
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingBallot.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingBallot.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingBallotGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingBallotGetValueSuccessDelegate, FGs2MatchmakingBallotValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingBallotGetValueErrorDelegate, FGs2MatchmakingBallotValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingBallotGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingOwnBallot Ballot;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2MatchmakingBallotGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2MatchmakingBallotGetValueErrorDelegate OnError;

    UGs2MatchmakingBallotGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Fetch::GetValueOfBallot", Category="Game Server Services|GS2-Matchmaking|Namespace|User|Ballot|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingBallotGetValueAsyncFunction* BallotGetValue(
        UObject* WorldContextObject,
        FGs2MatchmakingOwnBallot Ballot
    );

    virtual void Activate() override;
};