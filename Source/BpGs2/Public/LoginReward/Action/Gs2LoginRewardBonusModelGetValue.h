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
#include "BpGs2/Public/LoginReward/Model/Gs2LoginRewardBonusModel.h"
#include "BpGs2/Public/LoginReward/Model/Gs2LoginRewardBonusModel.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LoginRewardBonusModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LoginRewardBonusModelGetValueSuccessDelegate, FGs2LoginRewardBonusModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LoginRewardBonusModelGetValueErrorDelegate, FGs2LoginRewardBonusModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LoginRewardBonusModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LoginRewardBonusModel BonusModel;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2LoginRewardBonusModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2LoginRewardBonusModelGetValueErrorDelegate OnError;

    UGs2LoginRewardBonusModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::LoginReward::Fetch::GetValueOfBonusModel", Category="Game Server Services|GS2-LoginReward|Namespace|BonusModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LoginRewardBonusModelGetValueAsyncFunction* BonusModelGetValue(
        UObject* WorldContextObject,
        FGs2LoginRewardBonusModel BonusModel
    );

    virtual void Activate() override;
};