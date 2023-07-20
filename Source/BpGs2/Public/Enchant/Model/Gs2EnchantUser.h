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
#include "Enchant/Domain/Model/Gs2EnchantEzUserGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnchantUser.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantOwnUser
{
    GENERATED_BODY()

    Gs2::UE5::Enchant::Domain::Model::FEzUserGameSessionDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2EnchantUserFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::OwnBalanceParameterStatus", Category="Game Server Services|GS2-Enchant|Namespace|User|BalanceParameterStatus", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="BalanceParameterStatus") FGs2EnchantOwnBalanceParameterStatus OwnBalanceParameterStatus(
        FGs2EnchantOwnUser User,
        FString ParameterName,
        FString PropertyId
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enchant::OwnRarityParameterStatus", Category="Game Server Services|GS2-Enchant|Namespace|User|RarityParameterStatus", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="RarityParameterStatus") FGs2EnchantOwnRarityParameterStatus OwnRarityParameterStatus(
        FGs2EnchantOwnUser User,
        FString ParameterName,
        FString PropertyId
    );
};