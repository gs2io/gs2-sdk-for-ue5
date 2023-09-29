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

#include "Friend/Action/Gs2FriendFollowUserGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FriendFollowUserGetValueAsyncFunction::UGs2FriendFollowUserGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendFollowUserGetValueAsyncFunction* UGs2FriendFollowUserGetValueAsyncFunction::FollowUserGetValue(
    UObject* WorldContextObject,
    FGs2FriendOwnFollowUser FollowUser
)
{
    UGs2FriendFollowUserGetValueAsyncFunction* Action = NewObject<UGs2FriendFollowUserGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (FollowUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFollowUserGetValueAsyncFunction::FollowUserGetValue] FollowUser parameter specification is missing."))
        return Action;
    }
    Action->FollowUser = FollowUser;
    return Action;
}

void UGs2FriendFollowUserGetValueAsyncFunction::Activate()
{
    auto Future = FollowUser.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzFollowUserToFGs2FriendFollowUserValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FriendFollowUserValue ReturnFollowUser;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFollowUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}