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
#include "Friend/Model/Gs2FriendFriendRequest.h"
#include "Friend/Model/Gs2FriendReceiveFriendRequest.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendActionAccept.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendAcceptSuccessDelegate, FGs2FriendOwnReceiveFriendRequest, ReceiveFriendRequest, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendAcceptErrorDelegate, FGs2FriendOwnReceiveFriendRequest, ReceiveFriendRequest, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendAcceptAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnReceiveFriendRequest ReceiveFriendRequest;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendAcceptSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendAcceptErrorDelegate OnError;

    UGs2FriendAcceptAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::ReceiveFriendRequest::Action::Accept", Category="Game Server Services|GS2-Friend|Namespace|User|ReceiveFriendRequest|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendAcceptAsyncFunction* Accept(
        UObject* WorldContextObject,
        FGs2FriendOwnReceiveFriendRequest ReceiveFriendRequest
    );

    virtual void Activate() override;
};