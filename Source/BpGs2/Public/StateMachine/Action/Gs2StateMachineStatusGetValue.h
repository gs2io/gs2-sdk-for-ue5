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
#include "BpGs2/Public/StateMachine/Model/Gs2StateMachineStatus.h"
#include "BpGs2/Public/StateMachine/Model/Gs2StateMachineStatus.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2StateMachineStatusGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineStatusGetValueSuccessDelegate, FGs2StateMachineStatusValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineStatusGetValueErrorDelegate, FGs2StateMachineStatusValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StateMachineStatusGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StateMachineOwnStatus Status;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2StateMachineStatusGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2StateMachineStatusGetValueErrorDelegate OnError;

    UGs2StateMachineStatusGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::StateMachine::Fetch::GetValueOfStatus", Category="Game Server Services|GS2-StateMachine|Namespace|User|Status|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StateMachineStatusGetValueAsyncFunction* StatusGetValue(
        UObject* WorldContextObject,
        FGs2StateMachineOwnStatus Status
    );

    virtual void Activate() override;
};