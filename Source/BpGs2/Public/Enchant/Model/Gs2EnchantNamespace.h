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
#include "Enchant/Domain/Model/Gs2EnchantEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnchantNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Enchant::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2EnchantNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::BalanceParameterModel", Category="Game Server Services|GS2-Enchant|Namespace|BalanceParameterModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="BalanceParameterModel") FGs2EnchantBalanceParameterModel BalanceParameterModel(
        FGs2EnchantNamespace Namespace,
        FString ParameterName
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::RarityParameterModel", Category="Game Server Services|GS2-Enchant|Namespace|RarityParameterModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="RarityParameterModel") FGs2EnchantRarityParameterModel RarityParameterModel(
        FGs2EnchantNamespace Namespace,
        FString ParameterName
    );
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::Me", Category="Game Server Services|GS2-Enchant|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2EnchantOwnUser Me(
        FGs2EnchantNamespace Namespace,
        FGs2AccessToken AccessToken
    );
};