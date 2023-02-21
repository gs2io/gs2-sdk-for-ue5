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

#include "Friend/Action/Gs2FriendProfileGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FriendProfileGetValueAsyncFunction::UGs2FriendProfileGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendProfileGetValueAsyncFunction* UGs2FriendProfileGetValueAsyncFunction::ProfileGetValue(
    UObject* WorldContextObject,
    FGs2FriendOwnProfile Profile
)
{
    UGs2FriendProfileGetValueAsyncFunction* Action = NewObject<UGs2FriendProfileGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Profile.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendProfileGetValueAsyncFunction::ProfileGetValue] Profile parameter specification is missing."))
        return Action;
    }
    Action->Profile = Profile;
    return Action;
}

void UGs2FriendProfileGetValueAsyncFunction::Activate()
{
    auto Future = Profile.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzProfileToFGs2FriendProfileValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FriendProfileValue ReturnProfile;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnProfile, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}