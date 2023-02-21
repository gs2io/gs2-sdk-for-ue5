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

#include "Inbox/Action/Gs2InboxActionRead.h"
#include "Core/BpGs2Constant.h"

UGs2InboxReadAsyncFunction::UGs2InboxReadAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InboxReadAsyncFunction* UGs2InboxReadAsyncFunction::Read(
    UObject* WorldContextObject,
    FGs2InboxOwnMessage Message
)
{
    UGs2InboxReadAsyncFunction* Action = NewObject<UGs2InboxReadAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Message.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxReadAsyncFunction::Read] Message parameter specification is missing."))
        return Action;
    }
    Action->Message = Message;
    return Action;
}

void UGs2InboxReadAsyncFunction::Activate()
{
    if (Message.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxReadAsyncFunction] Message parameter specification is missing."))
        return;
    }

    auto Future = Message.Value->Read(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2InboxOwnMessage ReturnMessage;
        ReturnMessage.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnMessage, ReturnError);
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