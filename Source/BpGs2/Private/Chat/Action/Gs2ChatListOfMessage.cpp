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

#include "Chat/Action/Gs2ChatListOfMessage.h"
#include "Chat/Model/Gs2ChatMessage.h"
#include "Core/BpGs2Constant.h"

UGs2ChatListOfMessageAsyncFunction::UGs2ChatListOfMessageAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatListOfMessageAsyncFunction* UGs2ChatListOfMessageAsyncFunction::ListOfMessage(
    UObject* WorldContextObject,
    FGs2ChatOwnRoom Room
)
{
    UGs2ChatListOfMessageAsyncFunction* Action = NewObject<UGs2ChatListOfMessageAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Room.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatListOfMessageAsyncFunction::ListOfMessage] Room parameter specification is missing."))
        return Action;
    }
    Action->Room = Room;
    return Action;
}

void UGs2ChatListOfMessageAsyncFunction::Activate()
{
    TArray<FGs2ChatMessageValue> ReturnMessages;
    FGs2Error ReturnError;
    const auto It = Room.Value->Messages(
    );
    for (auto v : *It)
    {
        ReturnMessages.Add(EzMessageToFGs2ChatMessageValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnMessages, ReturnError);
}