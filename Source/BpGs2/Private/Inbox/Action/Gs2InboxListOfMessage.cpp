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

#include "Inbox/Action/Gs2InboxListOfMessage.h"
#include "Inbox/Model/Gs2InboxMessage.h"
#include "Core/BpGs2Constant.h"

UGs2InboxListOfMessageAsyncFunction::UGs2InboxListOfMessageAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InboxListOfMessageAsyncFunction* UGs2InboxListOfMessageAsyncFunction::ListOfMessage(
    UObject* WorldContextObject,
    FGs2InboxOwnUser User
)
{
    UGs2InboxListOfMessageAsyncFunction* Action = NewObject<UGs2InboxListOfMessageAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InboxListOfMessageAsyncFunction::ListOfMessage] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2InboxListOfMessageAsyncFunction::Activate()
{
    TArray<FGs2InboxMessageValue> ReturnMessages;
    FGs2Error ReturnError;
    const auto It = User.Value->Messages(
    );
    for (auto v : *It)
    {
        ReturnMessages.Add(EzMessageToFGs2InboxMessageValue(v));
    }
    OnSuccess.Broadcast(ReturnMessages, ReturnError);
}