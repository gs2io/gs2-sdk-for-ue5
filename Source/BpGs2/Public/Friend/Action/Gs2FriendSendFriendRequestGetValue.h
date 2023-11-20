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
#include "Friend/Model/Gs2FriendFriendRequest.h"
#include "Friend/Model/Gs2FriendSendFriendRequest.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendSendFriendRequestGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendSendFriendRequestGetValueSuccessDelegate, FGs2FriendFriendRequest, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendSendFriendRequestGetValueErrorDelegate, FGs2FriendFriendRequest, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendSendFriendRequestGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnSendFriendRequest SendFriendRequest;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendSendFriendRequestGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendSendFriendRequestGetValueErrorDelegate OnError;

    UGs2FriendSendFriendRequestGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Fetch::GetValueOfSendFriendRequest", Category="Game Server Services|GS2-Friend|Namespace|User|SendFriendRequest|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendSendFriendRequestGetValueAsyncFunction* SendFriendRequestGetValue(
        UObject* WorldContextObject,
        FGs2FriendOwnSendFriendRequest SendFriendRequest
    );

    virtual void Activate() override;
};