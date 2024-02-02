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

#include "Ranking/Action/Gs2RankingRankingGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2RankingRankingGetValueAsyncFunction::UGs2RankingRankingGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingRankingGetValueAsyncFunction* UGs2RankingRankingGetValueAsyncFunction::RankingGetValue(
    UObject* WorldContextObject,
    FGs2RankingOwnRanking Ranking
)
{
    UGs2RankingRankingGetValueAsyncFunction* Action = NewObject<UGs2RankingRankingGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Ranking.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingRankingGetValueAsyncFunction::RankingGetValue] Ranking parameter specification is missing."))
        return Action;
    }
    Action->Ranking = Ranking;
    return Action;
}

void UGs2RankingRankingGetValueAsyncFunction::Activate()
{
    auto Future = Ranking.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzRankingToFGs2RankingRankingValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2RankingRankingValue ReturnRanking;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRanking, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}