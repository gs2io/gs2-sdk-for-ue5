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

#include "Ranking/Action/Gs2RankingActionSubscribe.h"
#include "Core/BpGs2Constant.h"

UGs2RankingSubscribeAsyncFunction::UGs2RankingSubscribeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingSubscribeAsyncFunction* UGs2RankingSubscribeAsyncFunction::Subscribe(
    UObject* WorldContextObject,
    FGs2RankingOwnRankingCategory RankingCategory,
    FString TargetUserId
)
{
    UGs2RankingSubscribeAsyncFunction* Action = NewObject<UGs2RankingSubscribeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingSubscribeAsyncFunction::Subscribe] RankingCategory parameter specification is missing."))
        return Action;
    }
    Action->RankingCategory = RankingCategory;
    Action->TargetUserId = TargetUserId;
    return Action;
}

void UGs2RankingSubscribeAsyncFunction::Activate()
{
    if (RankingCategory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingSubscribeAsyncFunction] RankingCategory parameter specification is missing."))
        return;
    }

    auto Future = RankingCategory.Value->Subscribe(
        TargetUserId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2RankingOwnSubscribeUser ReturnSubscribeUser;
        ReturnSubscribeUser.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSubscribeUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2RankingOwnSubscribeUser ReturnSubscribeUser;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSubscribeUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}