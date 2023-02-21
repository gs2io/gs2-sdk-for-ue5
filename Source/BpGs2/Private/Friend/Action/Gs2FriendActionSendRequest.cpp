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

#include "Friend/Action/Gs2FriendActionSendRequest.h"
#include "Core/BpGs2Constant.h"

UGs2FriendSendRequestAsyncFunction::UGs2FriendSendRequestAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendSendRequestAsyncFunction* UGs2FriendSendRequestAsyncFunction::SendRequest(
    UObject* WorldContextObject,
    FGs2FriendOwnUser User,
    FString TargetUserId
)
{
    UGs2FriendSendRequestAsyncFunction* Action = NewObject<UGs2FriendSendRequestAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendSendRequestAsyncFunction::SendRequest] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->TargetUserId = TargetUserId;
    return Action;
}

void UGs2FriendSendRequestAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendSendRequestAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->SendRequest(
        TargetUserId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FriendOwnSendFriendRequest ReturnFriendRequest;
        ReturnFriendRequest.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnFriendRequest, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FriendOwnSendFriendRequest ReturnFriendRequest;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFriendRequest, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}