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

#include "Friend/Action/Gs2FriendActionUnfollow.h"
#include "Core/BpGs2Constant.h"

UGs2FriendUnfollowAsyncFunction::UGs2FriendUnfollowAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendUnfollowAsyncFunction* UGs2FriendUnfollowAsyncFunction::Unfollow(
    UObject* WorldContextObject,
    FGs2FriendOwnFollowUser FollowUser
)
{
    UGs2FriendUnfollowAsyncFunction* Action = NewObject<UGs2FriendUnfollowAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (FollowUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUnfollowAsyncFunction::Unfollow] FollowUser parameter specification is missing."))
        return Action;
    }
    Action->FollowUser = FollowUser;
    return Action;
}

void UGs2FriendUnfollowAsyncFunction::Activate()
{
    if (FollowUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUnfollowAsyncFunction] FollowUser parameter specification is missing."))
        return;
    }

    auto Future = FollowUser.Value->Unfollow(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FriendOwnFollowUser ReturnFollowUser;
        ReturnFollowUser.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnFollowUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FriendOwnFollowUser ReturnFollowUser;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFollowUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}