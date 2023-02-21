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

#include "Friend/Action/Gs2FriendListOfReceiveFriendRequest.h"
#include "Friend/Model/Gs2FriendFriendRequest.h"
#include "Core/BpGs2Constant.h"

UGs2FriendListOfReceiveFriendRequestAsyncFunction::UGs2FriendListOfReceiveFriendRequestAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendListOfReceiveFriendRequestAsyncFunction* UGs2FriendListOfReceiveFriendRequestAsyncFunction::ListOfReceiveFriendRequest(
    UObject* WorldContextObject,
    FGs2FriendOwnUser User
)
{
    UGs2FriendListOfReceiveFriendRequestAsyncFunction* Action = NewObject<UGs2FriendListOfReceiveFriendRequestAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendListOfReceiveFriendRequestAsyncFunction::ListOfReceiveFriendRequest] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2FriendListOfReceiveFriendRequestAsyncFunction::Activate()
{
    TArray<FGs2FriendFriendRequest> ReturnReceiveFriendRequests;
    FGs2Error ReturnError;
    const auto It = User.Value->ReceiveRequests(
    );
    for (auto v : *It)
    {
        ReturnReceiveFriendRequests.Add(EzFriendRequestToFGs2FriendFriendRequest(v));
    }
    OnSuccess.Broadcast(ReturnReceiveFriendRequests, ReturnError);
}