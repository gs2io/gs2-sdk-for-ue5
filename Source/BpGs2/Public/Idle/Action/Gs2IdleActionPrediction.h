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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Idle/Model/Gs2IdleAcquireAction.h"
#include "Idle/Model/Gs2IdleStatus.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2IdleActionPrediction.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2IdlePredictionSuccessDelegate, const TArray<FGs2IdleAcquireAction>&, AcquireActions, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2IdlePredictionErrorDelegate, const TArray<FGs2IdleAcquireAction>&, AcquireActions, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2IdlePredictionAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2IdleOwnStatus Status;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2IdlePredictionSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2IdlePredictionErrorDelegate OnError;

    UGs2IdlePredictionAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Idle::Status::Action::Prediction", Category="Game Server Services|GS2-Idle|Namespace|User|Status|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2IdlePredictionAsyncFunction* Prediction(
        UObject* WorldContextObject,
        FGs2IdleOwnStatus Status
    );

    virtual void Activate() override;
};