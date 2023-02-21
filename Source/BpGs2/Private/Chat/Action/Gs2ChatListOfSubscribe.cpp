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

#include "Chat/Action/Gs2ChatListOfSubscribe.h"
#include "Chat/Model/Gs2ChatSubscribe.h"
#include "Core/BpGs2Constant.h"

UGs2ChatListOfSubscribeAsyncFunction::UGs2ChatListOfSubscribeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ChatListOfSubscribeAsyncFunction* UGs2ChatListOfSubscribeAsyncFunction::ListOfSubscribe(
    UObject* WorldContextObject,
    FGs2ChatOwnUser User
)
{
    UGs2ChatListOfSubscribeAsyncFunction* Action = NewObject<UGs2ChatListOfSubscribeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ChatListOfSubscribeAsyncFunction::ListOfSubscribe] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2ChatListOfSubscribeAsyncFunction::Activate()
{
    TArray<FGs2ChatSubscribeValue> ReturnSubscribes;
    FGs2Error ReturnError;
    const auto It = User.Value->Subscribes(
    );
    for (auto v : *It)
    {
        ReturnSubscribes.Add(EzSubscribeToFGs2ChatSubscribeValue(v));
    }
    OnSuccess.Broadcast(ReturnSubscribes, ReturnError);
}