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

#include "Ranking/Model/Gs2RankingUser.h"
#include "Ranking/Model/Gs2RankingSubscribeUser.h"
#include "Ranking/Model/Gs2RankingRanking.h"
#include "Ranking/Model/Gs2RankingScore.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Ranking/Model/Gs2RankingSubscribeUser.h"
#include "Ranking/Model/Gs2RankingRanking.h"
#include "Ranking/Model/Gs2RankingScore.h"
#include "Core/BpGs2Constant.h"

FGs2RankingOwnSubscribeUser UGs2RankingUserFunctionLibrary::OwnSubscribeUser(
    FGs2RankingOwnUser User,
    FString CategoryName,
    FString TargetUserId
)
{
    FGs2RankingOwnSubscribeUser Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnSubscribeUser] User parameter specification is missing."))
        return Return;
    }
    if (CategoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnSubscribeUser] CategoryName parameter specification is missing."))
        return Return;
    }
    if (TargetUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnSubscribeUser] TargetUserId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->SubscribeUser(
        CategoryName,
        TargetUserId
    );
    return Return;
}

FGs2RankingRanking UGs2RankingUserFunctionLibrary::Ranking(
    FGs2RankingUser User,
    FString CategoryName
)
{
    FGs2RankingRanking Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::Ranking] User parameter specification is missing."))
        return Return;
    }
    if (CategoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::Ranking] CategoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Ranking(
        CategoryName
    );
    return Return;
}

FGs2RankingOwnRanking UGs2RankingUserFunctionLibrary::OwnRanking(
    FGs2RankingOwnUser User,
    FString CategoryName
)
{
    FGs2RankingOwnRanking Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnRanking] User parameter specification is missing."))
        return Return;
    }
    if (CategoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnRanking] CategoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Ranking(
        CategoryName
    );
    return Return;
}

FGs2RankingOwnScore UGs2RankingUserFunctionLibrary::OwnScore(
    FGs2RankingOwnUser User,
    FString CategoryName,
    FString ScorerUserId,
    FString UniqueId
)
{
    FGs2RankingOwnScore Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnScore] User parameter specification is missing."))
        return Return;
    }
    if (CategoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnScore] CategoryName parameter specification is missing."))
        return Return;
    }
    if (ScorerUserId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnScore] ScorerUserId parameter specification is missing."))
        return Return;
    }
    if (UniqueId == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUserFunctionLibrary::OwnScore] UniqueId parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Score(
        CategoryName,
        ScorerUserId,
        UniqueId
    );
    return Return;
}