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
#include "Stamina/Model/Gs2StaminaNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2StaminaListOfStaminaModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaListOfStaminaModelSuccessDelegate, const TArray<FGs2StaminaStaminaModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2StaminaListOfStaminaModelErrorDelegate, const TArray<FGs2StaminaStaminaModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2StaminaListOfStaminaModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2StaminaNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StaminaListOfStaminaModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2StaminaListOfStaminaModelErrorDelegate OnError;

    UGs2StaminaListOfStaminaModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Stamina::Fetch::ListOfStaminaModel", Category="Game Server Services|GS2-Stamina|Namespace|StaminaModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2StaminaListOfStaminaModelAsyncFunction* ListOfStaminaModel(
        UObject* WorldContextObject,
        FGs2StaminaNamespace Namespace
    );

    virtual void Activate() override;
};