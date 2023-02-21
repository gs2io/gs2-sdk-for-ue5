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

#include "Friend/Action/Gs2FriendActionDeleteRequest.h"
#include "Core/BpGs2Constant.h"

UGs2FriendDeleteRequestAsyncFunction::UGs2FriendDeleteRequestAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendDeleteRequestAsyncFunction* UGs2FriendDeleteRequestAsyncFunction::DeleteRequest(
    UObject* WorldContextObject,
    FGs2FriendOwnSendFriendRequest SendFriendRequest
)
{
    UGs2FriendDeleteRequestAsyncFunction* Action = NewObject<UGs2FriendDeleteRequestAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SendFriendRequest.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendDeleteRequestAsyncFunction::DeleteRequest] SendFriendRequest parameter specification is missing."))
        return Action;
    }
    Action->SendFriendRequest = SendFriendRequest;
    return Action;
}

void UGs2FriendDeleteRequestAsyncFunction::Activate()
{
    if (SendFriendRequest.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendDeleteRequestAsyncFunction] SendFriendRequest parameter specification is missing."))
        return;
    }

    auto Future = SendFriendRequest.Value->DeleteRequest(
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