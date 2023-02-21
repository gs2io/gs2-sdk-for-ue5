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

#include "Friend/Action/Gs2FriendActionAccept.h"
#include "Core/BpGs2Constant.h"

UGs2FriendAcceptAsyncFunction::UGs2FriendAcceptAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendAcceptAsyncFunction* UGs2FriendAcceptAsyncFunction::Accept(
    UObject* WorldContextObject,
    FGs2FriendOwnReceiveFriendRequest ReceiveFriendRequest
)
{
    UGs2FriendAcceptAsyncFunction* Action = NewObject<UGs2FriendAcceptAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (ReceiveFriendRequest.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendAcceptAsyncFunction::Accept] ReceiveFriendRequest parameter specification is missing."))
        return Action;
    }
    Action->ReceiveFriendRequest = ReceiveFriendRequest;
    return Action;
}

void UGs2FriendAcceptAsyncFunction::Activate()
{
    if (ReceiveFriendRequest.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendAcceptAsyncFunction] ReceiveFriendRequest parameter specification is missing."))
        return;
    }

    auto Future = ReceiveFriendRequest.Value->Accept(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FriendOwnReceiveFriendRequest ReturnFriendRequest;
        ReturnFriendRequest.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnFriendRequest, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FriendOwnReceiveFriendRequest ReturnFriendRequest;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFriendRequest, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}