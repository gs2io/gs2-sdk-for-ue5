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
#include "BpGs2/Public/Limit/Model/Gs2LimitCounter.h"
#include "BpGs2/Public/Limit/Model/Gs2LimitCounter.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LimitCounterGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitCounterGetValueSuccessDelegate, FGs2LimitCounterValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitCounterGetValueErrorDelegate, FGs2LimitCounterValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LimitCounterGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LimitOwnCounter Counter;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2LimitCounterGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2LimitCounterGetValueErrorDelegate OnError;

    UGs2LimitCounterGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Limit::Fetch::GetValueOfCounter", Category="Game Server Services|GS2-Limit|Namespace|User|Counter|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LimitCounterGetValueAsyncFunction* CounterGetValue(
        UObject* WorldContextObject,
        FGs2LimitOwnCounter Counter
    );

    virtual void Activate() override;
};