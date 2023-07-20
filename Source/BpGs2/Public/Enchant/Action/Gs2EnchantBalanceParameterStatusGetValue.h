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
#include "BpGs2/Public/Enchant/Model/Gs2EnchantBalanceParameterStatus.h"
#include "BpGs2/Public/Enchant/Model/Gs2EnchantBalanceParameterStatus.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnchantBalanceParameterStatusGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantBalanceParameterStatusGetValueSuccessDelegate, FGs2EnchantBalanceParameterStatusValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantBalanceParameterStatusGetValueErrorDelegate, FGs2EnchantBalanceParameterStatusValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnchantBalanceParameterStatusGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnchantOwnBalanceParameterStatus BalanceParameterStatus;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2EnchantBalanceParameterStatusGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2EnchantBalanceParameterStatusGetValueErrorDelegate OnError;

    UGs2EnchantBalanceParameterStatusGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::Fetch::GetValueOfBalanceParameterStatus", Category="Game Server Services|GS2-Enchant|Namespace|User|BalanceParameterStatus|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnchantBalanceParameterStatusGetValueAsyncFunction* BalanceParameterStatusGetValue(
        UObject* WorldContextObject,
        FGs2EnchantOwnBalanceParameterStatus BalanceParameterStatus
    );

    virtual void Activate() override;
};