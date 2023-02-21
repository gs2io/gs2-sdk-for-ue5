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
#include "BpGs2/Public/Friend/Model/Gs2FriendFriendRequest.h"
#include "BpGs2/Public/Friend/Model/Gs2FriendSendFriendRequest.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendActionDeleteRequest.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendDeleteRequestSuccessDelegate, FGs2FriendOwnSendFriendRequest, SendFriendRequest, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendDeleteRequestErrorDelegate, FGs2FriendOwnSendFriendRequest, SendFriendRequest, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendDeleteRequestAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnSendFriendRequest SendFriendRequest;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2FriendDeleteRequestSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2FriendDeleteRequestErrorDelegate OnError;

    UGs2FriendDeleteRequestAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::SendFriendRequest::Action::DeleteRequest", Category="Game Server Services|GS2-Friend|Namespace|User|SendFriendRequest|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendDeleteRequestAsyncFunction* DeleteRequest(
        UObject* WorldContextObject,
        FGs2FriendOwnSendFriendRequest SendFriendRequest
    );

    virtual void Activate() override;
};