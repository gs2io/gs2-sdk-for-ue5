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
#include "BpGs2/Public/Stamina/Model/Gs2StaminaUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2StaminaListOfStamina.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaListOfStaminaSuccessDelegate, const TArray<FGs2StaminaStaminaValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaListOfStaminaErrorDelegate, const TArray<FGs2StaminaStaminaValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StaminaListOfStaminaAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StaminaOwnUser User;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2StaminaListOfStaminaSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2StaminaListOfStaminaErrorDelegate OnError;

    UGs2StaminaListOfStaminaAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Stamina::Fetch::ListOfStamina", Category="Game Server Services|GS2-Stamina|Namespace|User|Stamina|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StaminaListOfStaminaAsyncFunction* ListOfStamina(
        UObject* WorldContextObject,
        FGs2StaminaOwnUser User
    );

    virtual void Activate() override;
};