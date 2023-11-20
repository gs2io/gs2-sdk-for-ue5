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
#include "Friend/Model/Gs2FriendFriendUser.h"
#include "Friend/Model/Gs2FriendFriendUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendFriendUserGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendFriendUserGetValueSuccessDelegate, FGs2FriendFriendUserValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendFriendUserGetValueErrorDelegate, FGs2FriendFriendUserValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendFriendUserGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnFriendUser FriendUser;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendFriendUserGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendFriendUserGetValueErrorDelegate OnError;

    UGs2FriendFriendUserGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Fetch::GetValueOfFriendUser", Category="Game Server Services|GS2-Friend|Namespace|User|Friend|FriendUser|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendFriendUserGetValueAsyncFunction* FriendUserGetValue(
        UObject* WorldContextObject,
        FGs2FriendOwnFriendUser FriendUser
    );

    virtual void Activate() override;
};