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

#include "Friend/Action/Gs2FriendActionDeleteFriend.h"
#include "Core/BpGs2Constant.h"

UGs2FriendDeleteFriendAsyncFunction::UGs2FriendDeleteFriendAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendDeleteFriendAsyncFunction* UGs2FriendDeleteFriendAsyncFunction::DeleteFriend(
    UObject* WorldContextObject,
    FGs2FriendOwnFriendUser FriendUser
)
{
    UGs2FriendDeleteFriendAsyncFunction* Action = NewObject<UGs2FriendDeleteFriendAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (FriendUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendDeleteFriendAsyncFunction::DeleteFriend] FriendUser parameter specification is missing."))
        return Action;
    }
    Action->FriendUser = FriendUser;
    return Action;
}

void UGs2FriendDeleteFriendAsyncFunction::Activate()
{
    if (FriendUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendDeleteFriendAsyncFunction] FriendUser parameter specification is missing."))
        return;
    }

    auto Future = FriendUser.Value->DeleteFriend(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FriendOwnFriendUser ReturnFriendUser;
        ReturnFriendUser.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnFriendUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FriendOwnFriendUser ReturnFriendUser;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFriendUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}