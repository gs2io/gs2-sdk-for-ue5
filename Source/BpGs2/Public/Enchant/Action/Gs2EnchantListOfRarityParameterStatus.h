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
#include "Enchant/Model/Gs2EnchantUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnchantListOfRarityParameterStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantListOfRarityParameterStatusSuccessDelegate, const TArray<FGs2EnchantRarityParameterStatusValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnchantListOfRarityParameterStatusErrorDelegate, const TArray<FGs2EnchantRarityParameterStatusValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnchantListOfRarityParameterStatusAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnchantOwnUser User;

public:
    FString ParameterName;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantListOfRarityParameterStatusSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnchantListOfRarityParameterStatusErrorDelegate OnError;

    UGs2EnchantListOfRarityParameterStatusAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::Fetch::ListOfRarityParameterStatus", Category="Game Server Services|GS2-Enchant|Namespace|User|RarityParameterStatus|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnchantListOfRarityParameterStatusAsyncFunction* ListOfRarityParameterStatus(
        UObject* WorldContextObject,
        FGs2EnchantOwnUser User,
        FString ParameterName
    );

    virtual void Activate() override;
};