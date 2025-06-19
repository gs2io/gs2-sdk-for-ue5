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
#include "StateMachine/Model/Gs2StateMachineStatus.h"
#include "StateMachine/Model/Gs2StateMachineEvent.h"
#include "StateMachine/Model/Gs2StateMachineStatus.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2StateMachineActionReport.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineReportSuccessDelegate, FGs2StateMachineOwnStatus, Status, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineReportErrorDelegate, FGs2StateMachineOwnStatus, Status, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StateMachineReportAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StateMachineOwnStatus Status;
    TArray<FGs2StateMachineEvent> Events;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StateMachineReportSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StateMachineReportErrorDelegate OnError;

    UGs2StateMachineReportAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::StateMachine::Status::Action::Report", Category="Game Server Services|GS2-StateMachine|Namespace|User|Status|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StateMachineReportAsyncFunction* Report(
        UObject* WorldContextObject,
        FGs2StateMachineOwnStatus Status,
        TArray<FGs2StateMachineEvent> Events
    );

    virtual void Activate() override;
};