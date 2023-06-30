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

#include "Matchmaking/Action/Gs2MatchmakingListOfRatingModel.h"
#include "Matchmaking/Model/Gs2MatchmakingRatingModel.h"
#include "Core/BpGs2Constant.h"

UGs2MatchmakingListOfRatingModelAsyncFunction::UGs2MatchmakingListOfRatingModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MatchmakingListOfRatingModelAsyncFunction* UGs2MatchmakingListOfRatingModelAsyncFunction::ListOfRatingModel(
    UObject* WorldContextObject,
    FGs2MatchmakingNamespace Namespace
)
{
    UGs2MatchmakingListOfRatingModelAsyncFunction* Action = NewObject<UGs2MatchmakingListOfRatingModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingListOfRatingModelAsyncFunction::ListOfRatingModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2MatchmakingListOfRatingModelAsyncFunction::Activate()
{
    TArray<FGs2MatchmakingRatingModelValue> ReturnRatingModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingListOfRatingModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->RatingModels(
    );
    for (auto v : *It)
    {
        ReturnRatingModels.Add(EzRatingModelToFGs2MatchmakingRatingModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnRatingModels, ReturnError);
}