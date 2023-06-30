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

#include "Matchmaking/Action/Gs2MatchmakingListOfRating.h"
#include "Matchmaking/Model/Gs2MatchmakingRating.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingListOfRatingAsyncFunction::UGs2MatchmakingListOfRatingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingListOfRatingAsyncFunction* UGs2MatchmakingListOfRatingAsyncFunction::ListOfRating(
    UObject* WorldContextObject,
    FGs2MatchmakingOwnUser User
)
{
    UGs2MatchmakingListOfRatingAsyncFunction* Action = NewObject<UGs2MatchmakingListOfRatingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingListOfRatingAsyncFunction::ListOfRating] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2MatchmakingListOfRatingAsyncFunction::Activate()
{
    TArray<FGs2MatchmakingRatingValue> ReturnRatings;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingListOfRatingAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Ratings(
    );
    for (auto v : *It)
    {
        ReturnRatings.Add(EzRatingToFGs2MatchmakingRatingValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnRatings, ReturnError);
}