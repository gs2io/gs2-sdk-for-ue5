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

#pragma once

#include "CoreMinimal.h"
#include "Friend/Model/Gs2FriendProfile.h"
#include "Friend/Model/Gs2FriendProfile.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendActionUpdateProfile.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendUpdateProfileSuccessDelegate, FGs2FriendOwnProfile, Profile, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendUpdateProfileErrorDelegate, FGs2FriendOwnProfile, Profile, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendUpdateProfileAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnProfile Profile;
    FString PublicProfile;
    FString FollowerProfile;
    FString FriendProfile;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendUpdateProfileSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendUpdateProfileErrorDelegate OnError;

    UGs2FriendUpdateProfileAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Profile::Action::UpdateProfile", Category="Game Server Services|GS2-Friend|Namespace|User|Profile|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendUpdateProfileAsyncFunction* UpdateProfile(
        UObject* WorldContextObject,
        FGs2FriendOwnProfile Profile,
        FString PublicProfile,
        FString FollowerProfile,
        FString FriendProfile
    );

    virtual void Activate() override;
};