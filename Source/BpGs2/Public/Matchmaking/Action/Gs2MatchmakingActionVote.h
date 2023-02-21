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
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingGameResult.h"
#include "BpGs2/Public/Matchmaking/Model/Gs2MatchmakingNamespace.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MatchmakingActionVote.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingVoteSuccessDelegate, FGs2MatchmakingBallot, Ballot, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MatchmakingVoteErrorDelegate, FGs2MatchmakingBallot, Ballot, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MatchmakingVoteAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MatchmakingNamespace Namespace;
    FString BallotBody;
    FString BallotSignature;
    TArray<FGs2MatchmakingGameResult> GameResults;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2MatchmakingVoteSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2MatchmakingVoteErrorDelegate OnError;

    UGs2MatchmakingVoteAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Matchmaking::Vote::Action::Vote", Category="Game Server Services|GS2-Matchmaking|Namespace|Vote|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MatchmakingVoteAsyncFunction* Vote(
        UObject* WorldContextObject,
        FGs2MatchmakingNamespace Namespace,
        FString BallotBody,
        FString BallotSignature,
        TArray<FGs2MatchmakingGameResult> GameResults
    );

    virtual void Activate() override;
};