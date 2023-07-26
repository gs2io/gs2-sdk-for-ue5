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
#include "Gs2StateMachineActionEmit.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineEmitSuccessDelegate, FGs2StateMachineOwnStatus, Status, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineEmitErrorDelegate, FGs2StateMachineOwnStatus, Status, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StateMachineEmitAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StateMachineOwnStatus Status;
    FString EventName;
    FString Args;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2StateMachineEmitSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2StateMachineEmitErrorDelegate OnError;

    UGs2StateMachineEmitAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::StateMachine::Status::Action::Emit", Category="Game Server Services|GS2-StateMachine|Namespace|User|Status|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StateMachineEmitAsyncFunction* Emit(
        UObject* WorldContextObject,
        FGs2StateMachineOwnStatus Status,
        FString EventName,
        FString Args
    );

    virtual void Activate() override;
};