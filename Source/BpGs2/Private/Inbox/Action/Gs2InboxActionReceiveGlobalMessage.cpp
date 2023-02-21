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

#include "Inbox/Action/Gs2InboxActionReceiveGlobalMessage.h"
#include "Core/BpGs2Constant.h"

UGs2InboxReceiveGlobalMessageAsyncFunction::UGs2InboxReceiveGlobalMessageAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InboxReceiveGlobalMessageAsyncFunction* UGs2InboxReceiveGlobalMessageAsyncFunction::ReceiveGlobalMessage(
    UObject* WorldContextObject,
    FGs2InboxOwnUser User
)
{
    UGs2InboxReceiveGlobalMessageAsyncFunction* Action = NewObject<UGs2InboxReceiveGlobalMessageAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxReceiveGlobalMessageAsyncFunction::ReceiveGlobalMessage] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2InboxReceiveGlobalMessageAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxReceiveGlobalMessageAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->ReceiveGlobalMessage(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        TArray<FGs2InboxOwnMessage> ReturnMessage;
        for (int i=0; i<Result->Num(); i++)
        {
            FGs2InboxOwnMessage r;
            r.Value = (*Result)[i];
            ReturnMessage.Add(r);
        }
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnMessage, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        TArray<FGs2InboxOwnMessage> ReturnMessage;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnSuccess.Broadcast(ReturnMessage, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}