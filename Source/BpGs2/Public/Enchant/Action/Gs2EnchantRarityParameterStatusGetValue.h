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
#include "Enchant/Model/Gs2EnchantRarityParameterStatus.h"
#include "Enchant/Model/Gs2EnchantRarityParameterStatus.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnchantRarityParameterStatusGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantRarityParameterStatusGetValueSuccessDelegate, FGs2EnchantRarityParameterStatusValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantRarityParameterStatusGetValueErrorDelegate, FGs2EnchantRarityParameterStatusValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnchantRarityParameterStatusGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnchantOwnRarityParameterStatus RarityParameterStatus;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantRarityParameterStatusGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantRarityParameterStatusGetValueErrorDelegate OnError;

    UGs2EnchantRarityParameterStatusGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::Fetch::GetValueOfRarityParameterStatus", Category="Game Server Services|GS2-Enchant|Namespace|User|RarityParameterStatus|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnchantRarityParameterStatusGetValueAsyncFunction* RarityParameterStatusGetValue(
        UObject* WorldContextObject,
        FGs2EnchantOwnRarityParameterStatus RarityParameterStatus
    );

    virtual void Activate() override;
};