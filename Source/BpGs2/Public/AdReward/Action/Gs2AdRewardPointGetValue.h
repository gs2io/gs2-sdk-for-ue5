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
#include "AdReward/Model/Gs2AdRewardPoint.h"
#include "AdReward/Model/Gs2AdRewardPoint.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AdRewardPointGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AdRewardPointGetValueSuccessDelegate, FGs2AdRewardPointValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AdRewardPointGetValueErrorDelegate, FGs2AdRewardPointValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AdRewardPointGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AdRewardOwnPoint Point;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AdRewardPointGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AdRewardPointGetValueErrorDelegate OnError;

    UGs2AdRewardPointGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::AdReward::Fetch::GetValueOfPoint", Category="Game Server Services|GS2-AdReward|Namespace|User|Point|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AdRewardPointGetValueAsyncFunction* PointGetValue(
        UObject* WorldContextObject,
        FGs2AdRewardOwnPoint Point
    );

    virtual void Activate() override;
};