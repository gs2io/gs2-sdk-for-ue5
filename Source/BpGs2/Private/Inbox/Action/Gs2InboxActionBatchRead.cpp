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

#include "Inbox/Action/Gs2InboxActionBatchRead.h"
#include "Core/BpGs2Constant.h"

UGs2InboxBatchReadAsyncFunction::UGs2InboxBatchReadAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InboxBatchReadAsyncFunction* UGs2InboxBatchReadAsyncFunction::BatchRead(
    UObject* WorldContextObject,
    FGs2InboxOwnUser User,
    TArray<FString> MessageNames
)
{
    UGs2InboxBatchReadAsyncFunction* Action = NewObject<UGs2InboxBatchReadAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxBatchReadAsyncFunction::BatchRead] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->MessageNames = MessageNames;
    return Action;
}

void UGs2InboxBatchReadAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxBatchReadAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->BatchRead(
        MessageNames
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