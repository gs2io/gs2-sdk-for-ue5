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
#include "Enhance/Model/Gs2EnhanceRateModel.h"
#include "Enhance/Model/Gs2EnhanceRateModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnhanceRateModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceRateModelGetValueSuccessDelegate, FGs2EnhanceRateModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceRateModelGetValueErrorDelegate, FGs2EnhanceRateModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnhanceRateModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnhanceRateModel RateModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceRateModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceRateModelGetValueErrorDelegate OnError;

    UGs2EnhanceRateModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enhance::Fetch::GetValueOfRateModel", Category="Game Server Services|GS2-Enhance|Namespace|RateModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnhanceRateModelGetValueAsyncFunction* RateModelGetValue(
        UObject* WorldContextObject,
        FGs2EnhanceRateModel RateModel
    );

    virtual void Activate() override;
};