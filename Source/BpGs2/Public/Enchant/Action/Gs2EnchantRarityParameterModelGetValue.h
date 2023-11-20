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
#include "Enchant/Model/Gs2EnchantRarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantRarityParameterModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnchantRarityParameterModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantRarityParameterModelGetValueSuccessDelegate, FGs2EnchantRarityParameterModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantRarityParameterModelGetValueErrorDelegate, FGs2EnchantRarityParameterModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnchantRarityParameterModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnchantRarityParameterModel RarityParameterModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantRarityParameterModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantRarityParameterModelGetValueErrorDelegate OnError;

    UGs2EnchantRarityParameterModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::Fetch::GetValueOfRarityParameterModel", Category="Game Server Services|GS2-Enchant|Namespace|RarityParameterModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnchantRarityParameterModelGetValueAsyncFunction* RarityParameterModelGetValue(
        UObject* WorldContextObject,
        FGs2EnchantRarityParameterModel RarityParameterModel
    );

    virtual void Activate() override;
};