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

#include "Friend/Action/Gs2FriendFriendUserGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FriendFriendUserGetValueAsyncFunction::UGs2FriendFriendUserGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendFriendUserGetValueAsyncFunction* UGs2FriendFriendUserGetValueAsyncFunction::FriendUserGetValue(
    UObject* WorldContextObject,
    FGs2FriendOwnFriendUser FriendUser
)
{
    UGs2FriendFriendUserGetValueAsyncFunction* Action = NewObject<UGs2FriendFriendUserGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (FriendUser.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendFriendUserGetValueAsyncFunction::FriendUserGetValue] FriendUser parameter specification is missing."))
        return Action;
    }
    Action->FriendUser = FriendUser;
    return Action;
}

void UGs2FriendFriendUserGetValueAsyncFunction::Activate()
{
    auto Future = FriendUser.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzFriendUserToFGs2FriendFriendUserValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FriendFriendUserValue ReturnFriendUser;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnFriendUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}