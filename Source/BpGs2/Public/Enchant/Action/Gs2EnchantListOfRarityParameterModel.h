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
#include "Enchant/Model/Gs2EnchantNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnchantListOfRarityParameterModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantListOfRarityParameterModelSuccessDelegate, const TArray<FGs2EnchantRarityParameterModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantListOfRarityParameterModelErrorDelegate, const TArray<FGs2EnchantRarityParameterModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnchantListOfRarityParameterModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnchantNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantListOfRarityParameterModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantListOfRarityParameterModelErrorDelegate OnError;

    UGs2EnchantListOfRarityParameterModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::Fetch::ListOfRarityParameterModel", Category="Game Server Services|GS2-Enchant|Namespace|RarityParameterModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnchantListOfRarityParameterModelAsyncFunction* ListOfRarityParameterModel(
        UObject* WorldContextObject,
        FGs2EnchantNamespace Namespace
    );

    virtual void Activate() override;
};