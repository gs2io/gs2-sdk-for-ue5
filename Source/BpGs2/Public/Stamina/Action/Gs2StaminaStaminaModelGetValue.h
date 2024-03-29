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
#include "Stamina/Model/Gs2StaminaStaminaModel.h"
#include "Stamina/Model/Gs2StaminaStaminaModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2StaminaStaminaModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaStaminaModelGetValueSuccessDelegate, FGs2StaminaStaminaModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaStaminaModelGetValueErrorDelegate, FGs2StaminaStaminaModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StaminaStaminaModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StaminaStaminaModel StaminaModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StaminaStaminaModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StaminaStaminaModelGetValueErrorDelegate OnError;

    UGs2StaminaStaminaModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Stamina::Fetch::GetValueOfStaminaModel", Category="Game Server Services|GS2-Stamina|Namespace|StaminaModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StaminaStaminaModelGetValueAsyncFunction* StaminaModelGetValue(
        UObject* WorldContextObject,
        FGs2StaminaStaminaModel StaminaModel
    );

    virtual void Activate() override;
};