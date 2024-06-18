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

#include "Matchmaking/Action/Gs2MatchmakingActionDoSeasonMatchmaking.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingDoSeasonMatchmakingAsyncFunction::UGs2MatchmakingDoSeasonMatchmakingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingDoSeasonMatchmakingAsyncFunction* UGs2MatchmakingDoSeasonMatchmakingAsyncFunction::DoSeasonMatchmaking(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnSeason Season
)
{
    UGs2MatchmakingDoSeasonMatchmakingAsyncFunction* Action = NewObject<UGs2MatchmakingDoSeasonMatchmakingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Season.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingDoSeasonMatchmakingAsyncFunction::DoSeasonMatchmaking] Season parameter specification is missing."))
        return Action;
    }
    Action->Season = Season;
    return Action;
}

void UGs2MatchmakingDoSeasonMatchmakingAsyncFunction::Activate()
{
    if (Season.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingDoSeasonMatchmakingAsyncFunction] Season parameter specification is missing."))
        return;
    }

    auto Future = Season.Value->DoSeasonMatchmaking(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2MatchmakingOwnSeasonGathering ReturnSeasonGathering;
        ReturnSeasonGathering.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSeasonGathering, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2MatchmakingOwnSeasonGathering ReturnSeasonGathering;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSeasonGathering, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}