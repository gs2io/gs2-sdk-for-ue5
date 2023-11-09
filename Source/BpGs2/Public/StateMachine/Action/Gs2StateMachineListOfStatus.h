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
#include "BpGs2/Public/StateMachine/Model/Gs2StateMachineUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2StateMachineListOfStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineListOfStatusSuccessDelegate, const TArray<FGs2StateMachineStatusValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StateMachineListOfStatusErrorDelegate, const TArray<FGs2StateMachineStatusValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StateMachineListOfStatusAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StateMachineOwnUser User;

public:
    FString Status;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StateMachineListOfStatusSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StateMachineListOfStatusErrorDelegate OnError;

    UGs2StateMachineListOfStatusAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::StateMachine::Fetch::ListOfStatus", Category="Game Server Services|GS2-StateMachine|Namespace|User|Status|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StateMachineListOfStatusAsyncFunction* ListOfStatus(
        UObject* WorldContextObject,
        FGs2StateMachineOwnUser User,
        FString Status
    );

    virtual void Activate() override;
};