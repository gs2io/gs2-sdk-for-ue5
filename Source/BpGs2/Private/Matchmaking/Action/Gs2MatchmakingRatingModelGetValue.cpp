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

#include "Matchmaking/Action/Gs2MatchmakingRatingModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingRatingModelGetValueAsyncFunction::UGs2MatchmakingRatingModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingRatingModelGetValueAsyncFunction* UGs2MatchmakingRatingModelGetValueAsyncFunction::RatingModelGetValue(
    UObject* WorldContextObject,
    FGs2MatchmakingRatingModel RatingModel
)
{
    UGs2MatchmakingRatingModelGetValueAsyncFunction* Action = NewObject<UGs2MatchmakingRatingModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RatingModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingRatingModelGetValueAsyncFunction::RatingModelGetValue] RatingModel parameter specification is missing."))
        return Action;
    }
    Action->RatingModel = RatingModel;
    return Action;
}

void UGs2MatchmakingRatingModelGetValueAsyncFunction::Activate()
{
    auto Future = RatingModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzRatingModelToFGs2MatchmakingRatingModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MatchmakingRatingModelValue ReturnRatingModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRatingModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}