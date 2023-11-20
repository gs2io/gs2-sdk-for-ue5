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
#include "Enhance/Model/Gs2EnhanceRateModel.h"
#include "Enhance/Model/Gs2EnhanceMaterial.h"
#include "Enhance/Model/Gs2EnhanceConfig.h"
#include "Enhance/Model/Gs2EnhanceEnhance.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnhanceActionEnhance.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceEnhanceSuccessDelegate, FGs2EnhanceOwnEnhance, Enhance, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceEnhanceErrorDelegate, FGs2EnhanceOwnEnhance, Enhance, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnhanceEnhanceAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    UPARAM(DisplayName="Enhance") FGs2EnhanceOwnEnhance EnhanceValue;
    FString RateName;
    FString TargetItemSetId;
    TArray<FGs2EnhanceMaterial> Materials;
    TArray<FGs2EnhanceConfig> Config;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceEnhanceSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceEnhanceErrorDelegate OnError;

    UGs2EnhanceEnhanceAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enhance::Enhance::Action::Enhance", Category="Game Server Services|GS2-Enhance|Namespace|User|Enhance|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnhanceEnhanceAsyncFunction* Enhance(
        UObject* WorldContextObject,
        FGs2EnhanceOwnEnhance Enhance,
        FString RateName,
        FString TargetItemSetId,
        TArray<FGs2EnhanceMaterial> Materials,
        TArray<FGs2EnhanceConfig> Config
    );

    virtual void Activate() override;
};