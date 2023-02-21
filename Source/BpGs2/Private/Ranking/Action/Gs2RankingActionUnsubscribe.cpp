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

#include "Ranking/Action/Gs2RankingActionUnsubscribe.h"
#include "Core/BpGs2Constant.h"

UGs2RankingUnsubscribeAsyncFunction::UGs2RankingUnsubscribeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2RankingUnsubscribeAsyncFunction* UGs2RankingUnsubscribeAsyncFunction::Unsubscribe(
    UObject* WorldContextObject,
    FGs2RankingOwnSubscribeUser SubscribeUser
)
{
    UGs2RankingUnsubscribeAsyncFunction* Action = NewObject<UGs2RankingUnsubscribeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SubscribeUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUnsubscribeAsyncFunction::Unsubscribe] SubscribeUser parameter specification is missing."))
        return Action;
    }
    Action->SubscribeUser = SubscribeUser;
    return Action;
}

void UGs2RankingUnsubscribeAsyncFunction::Activate()
{
    if (SubscribeUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingUnsubscribeAsyncFunction] SubscribeUser parameter specification is missing."))
        return;
    }

    auto Future = SubscribeUser.Value->Unsubscribe(
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