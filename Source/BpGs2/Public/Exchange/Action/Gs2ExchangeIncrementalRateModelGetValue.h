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
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeIncrementalRateModel.h"
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeIncrementalRateModel.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExchangeIncrementalRateModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeIncrementalRateModelGetValueSuccessDelegate, FGs2ExchangeIncrementalRateModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeIncrementalRateModelGetValueErrorDelegate, FGs2ExchangeIncrementalRateModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExchangeIncrementalRateModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ExchangeIncrementalRateModel IncrementalRateModel;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2ExchangeIncrementalRateModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2ExchangeIncrementalRateModelGetValueErrorDelegate OnError;

    UGs2ExchangeIncrementalRateModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::Fetch::GetValueOfIncrementalRateModel", Category="Game Server Services|GS2-Exchange|Namespace|IncrementalRateModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExchangeIncrementalRateModelGetValueAsyncFunction* IncrementalRateModelGetValue(
        UObject* WorldContextObject,
        FGs2ExchangeIncrementalRateModel IncrementalRateModel
    );

    virtual void Activate() override;
};