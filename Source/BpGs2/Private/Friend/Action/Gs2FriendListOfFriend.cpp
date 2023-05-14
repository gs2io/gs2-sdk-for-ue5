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

#include "Friend/Action/Gs2FriendListOfFriend.h"
#include "Friend/Model/Gs2FriendFriend.h"
#include "Friend/Model/Gs2FriendFriendUser.h"
#include "Core/BpGs2Constant.h"

UGs2FriendListOfFriendAsyncFunction::UGs2FriendListOfFriendAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendListOfFriendAsyncFunction* UGs2FriendListOfFriendAsyncFunction::ListOfFriend(
    UObject* WorldContextObject,
    FGs2FriendOwnUser User,
    bool WithProfile
)
{
    UGs2FriendListOfFriendAsyncFunction* Action = NewObject<UGs2FriendListOfFriendAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendListOfFriendAsyncFunction::ListOfFriend] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->WithProfile = WithProfile;
    return Action;
}

void UGs2FriendListOfFriendAsyncFunction::Activate()
{
    TArray<FGs2FriendFriendUserValue> ReturnFriends;
    FGs2Error ReturnError;
    const auto It = User.Value->Friends(
        WithProfile
    );
    for (auto v : *It)
    {
        ReturnFriends.Add(EzFriendUserToFGs2FriendFriendUserValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnFriends, ReturnError);
}