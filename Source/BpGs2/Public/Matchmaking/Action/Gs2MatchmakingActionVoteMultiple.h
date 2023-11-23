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
#include "Matchmaking/Model/Gs2MatchmakingBallot.h"
#include "Matchmaking/Model/Gs2MatchmakingSignedBallot.h"
#include "Matchmaking/Model/Gs2MatchmakingGameResult.h"
#include "Matchmaking/Model/Gs2MatchmakingNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingActionVoteMultiple.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingVoteMultipleSuccessDelegate, FGs2MatchmakingBallot, Ballot, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingVoteMultipleErrorDelegate, FGs2MatchmakingBallot, Ballot, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingVoteMultipleAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingNamespace Namespace;
    TArray<FGs2MatchmakingSignedBallot> SignedBallots;
    TArray<FGs2MatchmakingGameResult> GameResults;
    FString KeyId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingVoteMultipleSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MatchmakingVoteMultipleErrorDelegate OnError;

    UGs2MatchmakingVoteMultipleAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Vote::Action::VoteMultiple", Category="Game Server Services|GS2-Matchmaking|Namespace|Vote|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingVoteMultipleAsyncFunction* VoteMultiple(
        UObject* WorldContextObject,
        FGs2MatchmakingNamespace Namespace,
        TArray<FGs2MatchmakingSignedBallot> SignedBallots,
        TArray<FGs2MatchmakingGameResult> GameResults,
        FString KeyId
    );

    virtual void Activate() override;
};