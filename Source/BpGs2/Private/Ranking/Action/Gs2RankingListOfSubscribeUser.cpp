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

#include "Ranking/Action/Gs2RankingListOfSubscribeUser.h"
#include "Ranking/Model/Gs2RankingSubscribeUser.h"
#include "Core/BpGs2Constant.h"

UGs2RankingListOfSubscribeUserAsyncFunction::UGs2RankingListOfSubscribeUserAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingListOfSubscribeUserAsyncFunction* UGs2RankingListOfSubscribeUserAsyncFunction::ListOfSubscribeUser(
    UObject* WorldContextObject,
    FGs2RankingOwnRankingCategory RankingCategory
)
{
    UGs2RankingListOfSubscribeUserAsyncFunction* Action = NewObject<UGs2RankingListOfSubscribeUserAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingListOfSubscribeUserAsyncFunction::ListOfSubscribeUser] RankingCategory parameter specification is missing."))
        return Action;
    }
    Action->RankingCategory = RankingCategory;
    return Action;
}

void UGs2RankingListOfSubscribeUserAsyncFunction::Activate()
{
    TArray<FGs2RankingSubscribeUserValue> ReturnSubscribeUsers;
    FGs2Error ReturnError;

    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingListOfSubscribeUserAsyncFunction::Activate] RankingCategory parameter specification is missing."))
        return;
    }
    const auto It = RankingCategory.Value->SubscribeUsers(
    );
    for (auto v : *It)
    {
        ReturnSubscribeUsers.Add(EzSubscribeUserToFGs2RankingSubscribeUserValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnSubscribeUsers, ReturnError);
}