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

#include "Friend/Action/Gs2FriendActionUpdateProfile.h"
#include "Core/BpGs2Constant.h"

UGs2FriendUpdateProfileAsyncFunction::UGs2FriendUpdateProfileAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FriendUpdateProfileAsyncFunction* UGs2FriendUpdateProfileAsyncFunction::UpdateProfile(
    UObject* WorldContextObject,
    FGs2FriendOwnProfile Profile,
    FString PublicProfile,
    FString FollowerProfile,
    FString FriendProfile
)
{
    UGs2FriendUpdateProfileAsyncFunction* Action = NewObject<UGs2FriendUpdateProfileAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Profile.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUpdateProfileAsyncFunction::UpdateProfile] Profile parameter specification is missing."))
        return Action;
    }
    Action->Profile = Profile;
    Action->PublicProfile = PublicProfile;
    Action->FollowerProfile = FollowerProfile;
    Action->FriendProfile = FriendProfile;
    return Action;
}

void UGs2FriendUpdateProfileAsyncFunction::Activate()
{
    if (Profile.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FriendUpdateProfileAsyncFunction] Profile parameter specification is missing."))
        return;
    }

    auto Future = Profile.Value->UpdateProfile(
        PublicProfile,
        FollowerProfile,
        FriendProfile
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2FriendOwnProfile ReturnProfile;
        ReturnProfile.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnProfile, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2FriendOwnProfile ReturnProfile;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnProfile, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}