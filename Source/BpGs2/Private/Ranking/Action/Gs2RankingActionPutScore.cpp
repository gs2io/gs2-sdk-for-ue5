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

#include "Ranking/Action/Gs2RankingActionPutScore.h"
#include "Core/BpGs2Constant.h"

UGs2RankingPutScoreAsyncFunction::UGs2RankingPutScoreAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingPutScoreAsyncFunction* UGs2RankingPutScoreAsyncFunction::PutScore(
    UObject* WorldContextObject,
    FGs2RankingOwnRankingCategory RankingCategory,
    int64 Score,
    FString Metadata
)
{
    UGs2RankingPutScoreAsyncFunction* Action = NewObject<UGs2RankingPutScoreAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingPutScoreAsyncFunction::PutScore] RankingCategory parameter specification is missing."))
        return Action;
    }
    Action->RankingCategory = RankingCategory;
    Action->Score = Score;
    Action->Metadata = Metadata;
    return Action;
}

void UGs2RankingPutScoreAsyncFunction::Activate()
{
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingPutScoreAsyncFunction] RankingCategory parameter specification is missing."))
        return;
    }

    auto Future = RankingCategory.Value->PutScore(
        Score,
        Metadata
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2RankingOwnScore ReturnScore;
        ReturnScore.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnScore, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2RankingOwnScore ReturnScore;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnScore, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}