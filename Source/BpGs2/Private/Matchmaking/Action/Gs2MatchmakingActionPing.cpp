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

#include "Matchmaking/Action/Gs2MatchmakingActionPing.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingPingAsyncFunction::UGs2MatchmakingPingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingPingAsyncFunction* UGs2MatchmakingPingAsyncFunction::Ping(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnGathering Gathering
)
{
    UGs2MatchmakingPingAsyncFunction* Action = NewObject<UGs2MatchmakingPingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Gathering.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingPingAsyncFunction::Ping] Gathering parameter specification is missing."))
        return Action;
    }
    Action->Gathering = Gathering;
    return Action;
}

void UGs2MatchmakingPingAsyncFunction::Activate()
{
    if (Gathering.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingPingAsyncFunction] Gathering parameter specification is missing."))
        return;
    }

    auto Future = Gathering.Value->Ping(
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