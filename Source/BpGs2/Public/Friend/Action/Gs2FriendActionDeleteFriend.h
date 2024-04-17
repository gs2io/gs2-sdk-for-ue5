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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Friend/Model/Gs2FriendFriendUser.h"
#include "Friend/Model/Gs2FriendFriendUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendActionDeleteFriend.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendDeleteFriendSuccessDelegate, FGs2FriendOwnFriendUser, FriendUser, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendDeleteFriendErrorDelegate, FGs2FriendOwnFriendUser, FriendUser, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendDeleteFriendAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnFriendUser FriendUser;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendDeleteFriendSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendDeleteFriendErrorDelegate OnError;

    UGs2FriendDeleteFriendAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::FriendUser::Action::DeleteFriend", Category="Game Server Services|GS2-Friend|Namespace|User|Friend|FriendUser|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendDeleteFriendAsyncFunction* DeleteFriend(
        UObject* WorldContextObject,
        FGs2FriendOwnFriendUser FriendUser
    );

    virtual void Activate() override;
};