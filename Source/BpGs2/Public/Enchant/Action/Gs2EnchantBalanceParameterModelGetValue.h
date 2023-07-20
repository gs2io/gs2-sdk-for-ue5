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
#include "BpGs2/Public/Enchant/Model/Gs2EnchantBalanceParameterModel.h"
#include "BpGs2/Public/Enchant/Model/Gs2EnchantBalanceParameterModel.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnchantBalanceParameterModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantBalanceParameterModelGetValueSuccessDelegate, FGs2EnchantBalanceParameterModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantBalanceParameterModelGetValueErrorDelegate, FGs2EnchantBalanceParameterModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnchantBalanceParameterModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnchantBalanceParameterModel BalanceParameterModel;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2EnchantBalanceParameterModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2EnchantBalanceParameterModelGetValueErrorDelegate OnError;

    UGs2EnchantBalanceParameterModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::Fetch::GetValueOfBalanceParameterModel", Category="Game Server Services|GS2-Enchant|Namespace|BalanceParameterModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnchantBalanceParameterModelGetValueAsyncFunction* BalanceParameterModelGetValue(
        UObject* WorldContextObject,
        FGs2EnchantBalanceParameterModel BalanceParameterModel
    );

    virtual void Activate() override;
};