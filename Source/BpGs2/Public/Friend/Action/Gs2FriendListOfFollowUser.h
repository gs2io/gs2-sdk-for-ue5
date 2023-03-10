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
#include "BpGs2/Public/Friend/Model/Gs2FriendUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendListOfFollowUser.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendListOfFollowUserSuccessDelegate, const TArray<FGs2FriendFollowUserValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendListOfFollowUserErrorDelegate, const TArray<FGs2FriendFollowUserValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendListOfFollowUserAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnUser User;

public:
    bool WithProfile;

    UPROPERTY(BlueprintAssignable)
    FGs2FriendListOfFollowUserSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2FriendListOfFollowUserErrorDelegate OnError;

    UGs2FriendListOfFollowUserAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Fetch::ListOfFollowUser", Category="Game Server Services|GS2-Friend|Namespace|User|FollowUser|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendListOfFollowUserAsyncFunction* ListOfFollowUser(
        UObject* WorldContextObject,
        FGs2FriendOwnUser User,
        bool WithProfile
    );

    virtual void Activate() override;
};