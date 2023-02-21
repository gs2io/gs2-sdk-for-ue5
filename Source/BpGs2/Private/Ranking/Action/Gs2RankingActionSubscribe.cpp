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
    FGs2RankingOwnUser User,
    FString CategoryName,
    FString TargetUserId
)
{
    UGs2RankingSubscribeAsyncFunction* Action = NewObject<UGs2RankingSubscribeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingSubscribeAsyncFunction::Subscribe] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->CategoryName = CategoryName;
    Action->TargetUserId = TargetUserId;
    return Action;
}

void UGs2RankingSubscribeAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingSubscribeAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->Subscribe(
        CategoryName,
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