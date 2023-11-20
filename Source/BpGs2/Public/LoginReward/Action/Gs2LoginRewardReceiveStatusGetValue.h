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
#include "LoginReward/Model/Gs2LoginRewardReceiveStatus.h"
#include "LoginReward/Model/Gs2LoginRewardReceiveStatus.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LoginRewardReceiveStatusGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LoginRewardReceiveStatusGetValueSuccessDelegate, FGs2LoginRewardReceiveStatusValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LoginRewardReceiveStatusGetValueErrorDelegate, FGs2LoginRewardReceiveStatusValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LoginRewardReceiveStatusGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LoginRewardOwnReceiveStatus ReceiveStatus;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LoginRewardReceiveStatusGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LoginRewardReceiveStatusGetValueErrorDelegate OnError;

    UGs2LoginRewardReceiveStatusGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::LoginReward::Fetch::GetValueOfReceiveStatus", Category="Game Server Services|GS2-LoginReward|Namespace|User|ReceiveStatus|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LoginRewardReceiveStatusGetValueAsyncFunction* ReceiveStatusGetValue(
        UObject* WorldContextObject,
        FGs2LoginRewardOwnReceiveStatus ReceiveStatus
    );

    virtual void Activate() override;
};