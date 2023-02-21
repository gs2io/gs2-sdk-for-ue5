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
#include "BpGs2/Public/Friend/Model/Gs2FriendBlackList.h"
#include "BpGs2/Public/Friend/Model/Gs2FriendBlackList.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FriendActionRegisterBlackList.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendRegisterBlackListSuccessDelegate, FGs2FriendOwnBlackList, BlackList, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FriendRegisterBlackListErrorDelegate, FGs2FriendOwnBlackList, BlackList, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FriendRegisterBlackListAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FriendOwnBlackList BlackList;
    FString TargetUserId;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2FriendRegisterBlackListSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2FriendRegisterBlackListErrorDelegate OnError;

    UGs2FriendRegisterBlackListAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Friend::BlackList::Action::RegisterBlackList", Category="Game Server Services|GS2-Friend|Namespace|User|BlackList|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FriendRegisterBlackListAsyncFunction* RegisterBlackList(
        UObject* WorldContextObject,
        FGs2FriendOwnBlackList BlackList,
        FString TargetUserId
    );

    virtual void Activate() override;
};