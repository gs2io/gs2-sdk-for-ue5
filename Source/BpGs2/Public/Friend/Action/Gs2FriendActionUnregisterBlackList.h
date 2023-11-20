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
#include "Friend/Model/Gs2FriendBlackList.h"
#include "Friend/Model/Gs2FriendBlackList.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendActionUnregisterBlackList.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendUnregisterBlackListSuccessDelegate, FGs2FriendOwnBlackList, BlackList, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendUnregisterBlackListErrorDelegate, FGs2FriendOwnBlackList, BlackList, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendUnregisterBlackListAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnBlackList BlackList;
    FString TargetUserId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendUnregisterBlackListSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FriendUnregisterBlackListErrorDelegate OnError;

    UGs2FriendUnregisterBlackListAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::BlackList::Action::UnregisterBlackList", Category="Game Server Services|GS2-Friend|Namespace|User|BlackList|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendUnregisterBlackListAsyncFunction* UnregisterBlackList(
        UObject* WorldContextObject,
        FGs2FriendOwnBlackList BlackList,
        FString TargetUserId
    );

    virtual void Activate() override;
};