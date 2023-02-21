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

#include "Chat/Action/Gs2ChatActionUnsubscribe.h"
#include "Core/BpGs2Constant.h"

UGs2ChatUnsubscribeAsyncFunction::UGs2ChatUnsubscribeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatUnsubscribeAsyncFunction* UGs2ChatUnsubscribeAsyncFunction::Unsubscribe(
    UObject* WorldContextObject,
    FGs2ChatOwnSubscribe Subscribe
)
{
    UGs2ChatUnsubscribeAsyncFunction* Action = NewObject<UGs2ChatUnsubscribeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Subscribe.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUnsubscribeAsyncFunction::Unsubscribe] Subscribe parameter specification is missing."))
        return Action;
    }
    Action->Subscribe = Subscribe;
    return Action;
}

void UGs2ChatUnsubscribeAsyncFunction::Activate()
{
    if (Subscribe.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatUnsubscribeAsyncFunction] Subscribe parameter specification is missing."))
        return;
    }

    auto Future = Subscribe.Value->Unsubscribe(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2ChatOwnSubscribe ReturnSubscribe;
        ReturnSubscribe.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSubscribe, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2ChatOwnSubscribe ReturnSubscribe;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSubscribe, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}