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

#include "Ranking/Action/Gs2RankingScoreGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2RankingScoreGetValueAsyncFunction::UGs2RankingScoreGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingScoreGetValueAsyncFunction* UGs2RankingScoreGetValueAsyncFunction::ScoreGetValue(
    UObject* WorldContextObject,
    FGs2RankingOwnScore Score
)
{
    UGs2RankingScoreGetValueAsyncFunction* Action = NewObject<UGs2RankingScoreGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Score.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingScoreGetValueAsyncFunction::ScoreGetValue] Score parameter specification is missing."))
        return Action;
    }
    Action->Score = Score;
    return Action;
}

void UGs2RankingScoreGetValueAsyncFunction::Activate()
{
    auto Future = Score.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzScoreToFGs2RankingScoreValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2RankingScoreValue ReturnScore;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnScore, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}