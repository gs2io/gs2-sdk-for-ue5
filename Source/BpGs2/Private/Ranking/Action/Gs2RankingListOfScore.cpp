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

#include "Ranking/Action/Gs2RankingListOfScore.h"
#include "Ranking/Model/Gs2RankingScore.h"
#include "Core/BpGs2Constant.h"

UGs2RankingListOfScoreAsyncFunction::UGs2RankingListOfScoreAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingListOfScoreAsyncFunction* UGs2RankingListOfScoreAsyncFunction::ListOfScore(
    UObject* WorldContextObject,
    FGs2RankingOwnUser User,
    FString CategoryName,
    FString ScorerUserId
)
{
    UGs2RankingListOfScoreAsyncFunction* Action = NewObject<UGs2RankingListOfScoreAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingListOfScoreAsyncFunction::ListOfScore] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->CategoryName = CategoryName;
    Action->ScorerUserId = ScorerUserId;
    return Action;
}

void UGs2RankingListOfScoreAsyncFunction::Activate()
{
    TArray<FGs2RankingScoreValue> ReturnScores;
    FGs2Error ReturnError;
    const auto It = User.Value->Scores(
        CategoryName,
        ScorerUserId
    );
    for (auto v : *It)
    {
        ReturnScores.Add(EzScoreToFGs2RankingScoreValue(v.Current()));
    }
    OnSuccess.Broadcast(ReturnScores, ReturnError);
}