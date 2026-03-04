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
#include "Enhance/Model/Gs2EnhanceUnleashRateModel.h"
#include "Enhance/Model/Gs2EnhanceUnleashRateModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnhanceUnleashRateModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceUnleashRateModelGetValueSuccessDelegate, FGs2EnhanceUnleashRateModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceUnleashRateModelGetValueErrorDelegate, FGs2EnhanceUnleashRateModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnhanceUnleashRateModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnhanceUnleashRateModel UnleashRateModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceUnleashRateModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceUnleashRateModelGetValueErrorDelegate OnError;

    UGs2EnhanceUnleashRateModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enhance::Fetch::GetValueOfUnleashRateModel", Category="Game Server Services|GS2-Enhance|Namespace|UnleashRateModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnhanceUnleashRateModelGetValueAsyncFunction* UnleashRateModelGetValue(
        UObject* WorldContextObject,
        FGs2EnhanceUnleashRateModel UnleashRateModel
    );

    virtual void Activate() override;
};