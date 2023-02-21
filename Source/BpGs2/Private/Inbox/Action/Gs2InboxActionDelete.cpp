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

#include "Inbox/Action/Gs2InboxActionDelete.h"
#include "Core/BpGs2Constant.h"

UGs2InboxDeleteAsyncFunction::UGs2InboxDeleteAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InboxDeleteAsyncFunction* UGs2InboxDeleteAsyncFunction::Delete(
    UObject* WorldContextObject,
    FGs2InboxOwnMessage Message
)
{
    UGs2InboxDeleteAsyncFunction* Action = NewObject<UGs2InboxDeleteAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Message.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxDeleteAsyncFunction::Delete] Message parameter specification is missing."))
        return Action;
    }
    Action->Message = Message;
    return Action;
}

void UGs2InboxDeleteAsyncFunction::Activate()
{
    if (Message.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxDeleteAsyncFunction] Message parameter specification is missing."))
        return;
    }

    auto Future = Message.Value->Delete(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2InboxOwnMessage ReturnMessage;
        ReturnMessage.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnMessage, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2InboxOwnMessage ReturnMessage;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnMessage, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}