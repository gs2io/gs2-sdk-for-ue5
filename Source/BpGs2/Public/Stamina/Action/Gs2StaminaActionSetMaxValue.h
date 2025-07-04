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
#include "Stamina/Model/Gs2StaminaStamina.h"
#include "Stamina/Model/Gs2StaminaStamina.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2StaminaActionSetMaxValue.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaSetMaxValueSuccessDelegate, FGs2StaminaOwnStamina, Stamina, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaSetMaxValueErrorDelegate, FGs2StaminaOwnStamina, Stamina, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StaminaSetMaxValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StaminaOwnStamina Stamina;
    FString SignedStatusBody;
    FString SignedStatusSignature;
    FString KeyId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StaminaSetMaxValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StaminaSetMaxValueErrorDelegate OnError;

    UGs2StaminaSetMaxValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Stamina::Stamina::Action::SetMaxValue", Category="Game Server Services|GS2-Stamina|Namespace|User|Stamina|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StaminaSetMaxValueAsyncFunction* SetMaxValue(
        UObject* WorldContextObject,
        FGs2StaminaOwnStamina Stamina,
        FString SignedStatusBody,
        FString SignedStatusSignature,
        FString KeyId
    );

    virtual void Activate() override;
};