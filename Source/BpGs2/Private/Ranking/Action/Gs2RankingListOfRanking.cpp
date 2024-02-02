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
 *
 * deny overwrite
 */

#include "Ranking/Action/Gs2RankingListOfRanking.h"
#include "Ranking/Model/Gs2RankingRanking.h"
#include "Core/BpGs2Constant.h"

UGs2RankingListOfRankingAsyncFunction::UGs2RankingListOfRankingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingListOfRankingAsyncFunction* UGs2RankingListOfRankingAsyncFunction::ListOfRanking(
    UObject* WorldContextObject,
    FGs2RankingOwnRankingCategory RankingCategory
)
{
    UGs2RankingListOfRankingAsyncFunction* Action = NewObject<UGs2RankingListOfRankingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingListOfRankingAsyncFunction::ListOfRanking] RankingCategory parameter specification is missing."))
        return Action;
    }
    Action->RankingCategory = RankingCategory;
    return Action;
}

void UGs2RankingListOfRankingAsyncFunction::Activate()
{
    TArray<FGs2RankingRankingValue> ReturnRankings;
    FGs2Error ReturnError;

    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingListOfRankingAsyncFunction::Activate] RankingCategory parameter specification is missing."))
        return;
    }
    const auto It = RankingCategory.Value->Rankings(
    );
    for (auto v : *It)
    {
        ReturnRankings.Add(EzRankingToFGs2RankingRankingValue(v.Current()));
    }
    OnSuccess.Broadcast(ReturnRankings, ReturnError);
}