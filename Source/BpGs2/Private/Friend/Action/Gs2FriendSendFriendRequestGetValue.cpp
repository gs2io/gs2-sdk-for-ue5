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

#include "Friend/Action/Gs2FriendSendFriendRequestGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FriendSendFriendRequestGetValueAsyncFunction::UGs2FriendSendFriendRequestGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendSendFriendRequestGetValueAsyncFunction* UGs2FriendSendFriendRequestGetValueAsyncFunction::SendFriendRequestGetValue(
    UObject* WorldContextObject,
    FGs2FriendOwnSendFriendRequest SendFriendRequest
)
{
    UGs2FriendSendFriendRequestGetValueAsyncFunction* Action = NewObject<UGs2FriendSendFriendRequestGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SendFriendRequest.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendSendFriendRequestGetValueAsyncFunction::SendFriendRequestGetValue] SendFriendRequest parameter specification is missing."))
        return Action;
    }
    Action->SendFriendRequest = SendFriendRequest;
    return Action;
}

void UGs2FriendSendFriendRequestGetValueAsyncFunction::Activate()
{
    auto Future = SendFriendRequest.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzFriendRequestToFGs2FriendFriendRequest(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FriendFriendRequest ReturnFriendRequest;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFriendRequest, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}