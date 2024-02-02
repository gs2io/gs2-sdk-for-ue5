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

#include "Friend/Action/Gs2FriendPublicProfileGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2FriendPublicProfileGetValueAsyncFunction::UGs2FriendPublicProfileGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendPublicProfileGetValueAsyncFunction* UGs2FriendPublicProfileGetValueAsyncFunction::PublicProfileGetValue(
    UObject* WorldContextObject,
    FGs2FriendPublicProfile PublicProfile
)
{
    UGs2FriendPublicProfileGetValueAsyncFunction* Action = NewObject<UGs2FriendPublicProfileGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (PublicProfile.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendPublicProfileGetValueAsyncFunction::PublicProfileGetValue] PublicProfile parameter specification is missing."))
        return Action;
    }
    Action->PublicProfile = PublicProfile;
    return Action;
}

void UGs2FriendPublicProfileGetValueAsyncFunction::Activate()
{
    auto Future = PublicProfile.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzPublicProfileToFGs2FriendPublicProfileValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2FriendPublicProfileValue ReturnPublicProfile;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnPublicProfile, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}