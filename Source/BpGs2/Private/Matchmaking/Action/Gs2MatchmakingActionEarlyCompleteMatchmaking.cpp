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

#include "Matchmaking/Action/Gs2MatchmakingActionEarlyCompleteMatchmaking.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction::UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction* UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction::EarlyCompleteMatchmaking(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnGathering Gathering
)
{
    UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction* Action = NewObject<UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Gathering.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction::EarlyCompleteMatchmaking] Gathering parameter specification is missing."))
        return Action;
    }
    Action->Gathering = Gathering;
    return Action;
}

void UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction::Activate()
{
    if (Gathering.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingEarlyCompleteMatchmakingAsyncFunction] Gathering parameter specification is missing."))
        return;
    }

    auto Future = Gathering.Value->EarlyCompleteMatchmaking(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2MatchmakingOwnGathering ReturnGathering;
        ReturnGathering.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnGathering, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2MatchmakingOwnGathering ReturnGathering;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnGathering, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}