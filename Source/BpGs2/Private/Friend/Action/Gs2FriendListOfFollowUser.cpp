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
 *
 * deny overwrite
 */

#include "Friend/Action/Gs2FriendListOfFollowUser.h"
#include "Friend/Model/Gs2FriendFollowUser.h"
#include "Core/BpGs2Constant.h"

UGs2FriendListOfFollowUserAsyncFunction::UGs2FriendListOfFollowUserAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendListOfFollowUserAsyncFunction* UGs2FriendListOfFollowUserAsyncFunction::ListOfFollowUser(
    UObject* WorldContextObject,
    FGs2FriendOwnFollow Follow
)
{
    UGs2FriendListOfFollowUserAsyncFunction* Action = NewObject<UGs2FriendListOfFollowUserAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Follow.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendListOfFollowUserAsyncFunction::ListOfFollowUser] Follow parameter specification is missing."))
        return Action;
    }
    Action->Follow = Follow;
    return Action;
}

void UGs2FriendListOfFollowUserAsyncFunction::Activate()
{
    TArray<FGs2FriendFollowUserValue> ReturnFollowUsers;
    FGs2Error ReturnError;

    if (Follow.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendListOfFollowUserAsyncFunction::Activate] Follow parameter specification is missing."))
        return;
    }
    const auto It = Follow.Value->Follows(
    );
    for (auto v : *It)
    {
        ReturnFollowUsers.Add(EzFollowUserToFGs2FriendFollowUserValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnFollowUsers, ReturnError);
}