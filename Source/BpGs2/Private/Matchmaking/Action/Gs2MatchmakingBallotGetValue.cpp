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

#include "Matchmaking/Action/Gs2MatchmakingBallotGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingBallotGetValueAsyncFunction::UGs2MatchmakingBallotGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingBallotGetValueAsyncFunction* UGs2MatchmakingBallotGetValueAsyncFunction::BallotGetValue(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnBallot Ballot
)
{
    UGs2MatchmakingBallotGetValueAsyncFunction* Action = NewObject<UGs2MatchmakingBallotGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Ballot.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingBallotGetValueAsyncFunction::BallotGetValue] Ballot parameter specification is missing."))
        return Action;
    }
    Action->Ballot = Ballot;
    return Action;
}

void UGs2MatchmakingBallotGetValueAsyncFunction::Activate()
{
    auto Future = Ballot.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBallotToFGs2MatchmakingBallotValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MatchmakingBallotValue ReturnBallot;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBallot, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}