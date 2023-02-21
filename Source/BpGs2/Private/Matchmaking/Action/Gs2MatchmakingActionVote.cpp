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

#include "Matchmaking/Action/Gs2MatchmakingActionVote.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingVoteAsyncFunction::UGs2MatchmakingVoteAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingVoteAsyncFunction* UGs2MatchmakingVoteAsyncFunction::Vote(
    UObject* WorldContextObject,
    FGs2MatchmakingNamespace Namespace,
    FString BallotBody,
    FString BallotSignature,
    TArray<FGs2MatchmakingGameResult> GameResults
)
{
    UGs2MatchmakingVoteAsyncFunction* Action = NewObject<UGs2MatchmakingVoteAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingVoteAsyncFunction::Vote] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    Action->BallotBody = BallotBody;
    Action->BallotSignature = BallotSignature;
    Action->GameResults = GameResults;
    return Action;
}

void UGs2MatchmakingVoteAsyncFunction::Activate()
{
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingVoteAsyncFunction] Namespace parameter specification is missing."))
        return;
    }

    auto Future = Namespace.Value->Vote(
        BallotBody,
        BallotSignature,
        [&]
        {
            TArray<Gs2::UE5::Matchmaking::Model::FEzGameResultPtr> r;
            for (auto v : GameResults)
            {
                r.Add(FGs2MatchmakingGameResultToEzGameResult(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2MatchmakingBallot ReturnBallot;
        ReturnBallot.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnBallot, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2MatchmakingBallot ReturnBallot;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBallot, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}