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

#include "Money2/Action/Gs2Money2ActionTakeOverSubscriptionStatus.h"
#include "Core/BpGs2Constant.h"

UGs2Money2TakeOverSubscriptionStatusAsyncFunction::UGs2Money2TakeOverSubscriptionStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2Money2TakeOverSubscriptionStatusAsyncFunction* UGs2Money2TakeOverSubscriptionStatusAsyncFunction::TakeOverSubscriptionStatus(
    UObject* WorldContextObject,
    FGs2Money2OwnUser User,
    FString Receipt
)
{
    UGs2Money2TakeOverSubscriptionStatusAsyncFunction* Action = NewObject<UGs2Money2TakeOverSubscriptionStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2TakeOverSubscriptionStatusAsyncFunction::TakeOverSubscriptionStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->Receipt = Receipt;
    return Action;
}

void UGs2Money2TakeOverSubscriptionStatusAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2TakeOverSubscriptionStatusAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->TakeOverSubscriptionStatus(
        Receipt
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2Money2OwnSubscriptionStatus ReturnSubscriptionStatus;
        ReturnSubscriptionStatus.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSubscriptionStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2Money2OwnSubscriptionStatus ReturnSubscriptionStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSubscriptionStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}