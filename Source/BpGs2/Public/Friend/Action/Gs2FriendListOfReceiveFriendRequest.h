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
#include "Friend/Model/Gs2FriendUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendListOfReceiveFriendRequest.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendListOfReceiveFriendRequestSuccessDelegate, const TArray<FGs2FriendFriendRequest>, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendListOfReceiveFriendRequestErrorDelegate, const TArray<FGs2FriendFriendRequest>, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendListOfReceiveFriendRequestAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendListOfReceiveFriendRequestSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendListOfReceiveFriendRequestErrorDelegate OnError;

    UGs2FriendListOfReceiveFriendRequestAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::Fetch::ListOfReceiveFriendRequest", Category="Game Server Services|GS2-Friend|Namespace|User|ReceiveFriendRequest|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendListOfReceiveFriendRequestAsyncFunction* ListOfReceiveFriendRequest(
        UObject* WorldContextObject,
        FGs2FriendOwnUser User
    );

    virtual void Activate() override;
};