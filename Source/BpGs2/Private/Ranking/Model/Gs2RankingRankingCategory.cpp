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

#include "Ranking/Model/Gs2RankingRankingCategory.h"
#include "Ranking/Model/Gs2RankingSubscribeUser.h"
#include "Ranking/Model/Gs2RankingRanking.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Ranking/Model/Gs2RankingSubscribeUser.h"
#include "Ranking/Model/Gs2RankingRanking.h"
#include "Core/BpGs2Constant.h"

FGs2RankingOwnSubscribeUser UGs2RankingRankingCategoryFunctionLibrary::OwnSubscribeUser(
    FGs2RankingOwnRankingCategory RankingCategory,
    FString TargetUserId
)
{
    FGs2RankingOwnSubscribeUser Return;
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingRankingCategoryFunctionLibrary::OwnSubscribeUser] RankingCategory parameter specification is missing."))
        return Return;
    }
    if (TargetUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingRankingCategoryFunctionLibrary::OwnSubscribeUser] TargetUserId parameter specification is missing."))
        return Return;
    }
    Return.Value = RankingCategory.Value->SubscribeUser(
        TargetUserId
    );
    return Return;
}

FGs2RankingRanking UGs2RankingRankingCategoryFunctionLibrary::Ranking(
    FGs2RankingRankingCategory RankingCategory,
    FString ScorerUserId,
    int64 Index
)
{
    FGs2RankingRanking Return;
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingRankingCategoryFunctionLibrary::Ranking] RankingCategory parameter specification is missing."))
        return Return;
    }
    Return.Value = RankingCategory.Value->Ranking(
        ScorerUserId,
        Index
    );
    return Return;
}

FGs2RankingOwnRanking UGs2RankingRankingCategoryFunctionLibrary::OwnRanking(
    FGs2RankingOwnRankingCategory RankingCategory,
    FString ScorerUserId,
    int64 Index
)
{
    FGs2RankingOwnRanking Return;
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingRankingCategoryFunctionLibrary::OwnRanking] RankingCategory parameter specification is missing."))
        return Return;
    }
    Return.Value = RankingCategory.Value->Ranking(
        ScorerUserId,
        Index
    );
    return Return;
}