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

#include "Matchmaking/Action/Gs2MatchmakingSeasonModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingSeasonModelGetValueAsyncFunction::UGs2MatchmakingSeasonModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingSeasonModelGetValueAsyncFunction* UGs2MatchmakingSeasonModelGetValueAsyncFunction::SeasonModelGetValue(
    UObject* WorldContextObject,
    FGs2MatchmakingSeasonModel SeasonModel
)
{
    UGs2MatchmakingSeasonModelGetValueAsyncFunction* Action = NewObject<UGs2MatchmakingSeasonModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SeasonModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingSeasonModelGetValueAsyncFunction::SeasonModelGetValue] SeasonModel parameter specification is missing."))
        return Action;
    }
    Action->SeasonModel = SeasonModel;
    return Action;
}

void UGs2MatchmakingSeasonModelGetValueAsyncFunction::Activate()
{
    auto Future = SeasonModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSeasonModelToFGs2MatchmakingSeasonModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MatchmakingSeasonModelValue ReturnSeasonModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSeasonModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}