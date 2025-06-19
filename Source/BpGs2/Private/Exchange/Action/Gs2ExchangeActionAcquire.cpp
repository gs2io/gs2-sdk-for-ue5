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

#include "Exchange/Action/Gs2ExchangeActionAcquire.h"
#include "Core/BpGs2Constant.h"

UGs2ExchangeAcquireAsyncFunction::UGs2ExchangeAcquireAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExchangeAcquireAsyncFunction* UGs2ExchangeAcquireAsyncFunction::Acquire(
    UObject* WorldContextObject,
    FGs2ExchangeOwnAwait Await
)
{
    UGs2ExchangeAcquireAsyncFunction* Action = NewObject<UGs2ExchangeAcquireAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Await.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeAcquireAsyncFunction::Acquire] Await parameter specification is missing."))
        return Action;
    }
    Action->Await = Await;
    return Action;
}

void UGs2ExchangeAcquireAsyncFunction::Activate()
{
    if (Await.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeAcquireAsyncFunction] Await parameter specification is missing."))
        return;
    }

    auto Future = Await.Value->Acquire(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}