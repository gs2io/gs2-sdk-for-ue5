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

#include "Matchmaking/Action/Gs2MatchmakingSeasonGatheringGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingSeasonGatheringGetValueAsyncFunction::UGs2MatchmakingSeasonGatheringGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingSeasonGatheringGetValueAsyncFunction* UGs2MatchmakingSeasonGatheringGetValueAsyncFunction::SeasonGatheringGetValue(
    UObject* WorldContextObject,
    FGs2MatchmakingSeasonGathering SeasonGathering
)
{
    UGs2MatchmakingSeasonGatheringGetValueAsyncFunction* Action = NewObject<UGs2MatchmakingSeasonGatheringGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SeasonGathering.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingSeasonGatheringGetValueAsyncFunction::SeasonGatheringGetValue] SeasonGathering parameter specification is missing."))
        return Action;
    }
    Action->SeasonGathering = SeasonGathering;
    return Action;
}

void UGs2MatchmakingSeasonGatheringGetValueAsyncFunction::Activate()
{
    auto Future = SeasonGathering.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSeasonGatheringToFGs2MatchmakingSeasonGatheringValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MatchmakingSeasonGatheringValue ReturnSeasonGathering;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSeasonGathering, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}