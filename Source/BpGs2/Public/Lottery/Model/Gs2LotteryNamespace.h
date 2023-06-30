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
#include "Lottery/Domain/Model/Gs2LotteryEzNamespaceDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2LotteryNamespace.generated.h"

USTRUCT(BlueprintType)
struct FGs2LotteryNamespace
{
    GENERATED_BODY()

    Gs2::UE5::Lottery::Domain::Model::FEzNamespaceDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2LotteryNamespaceFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Lottery::Me", Category="Game Server Services|GS2-Lottery|Namespace|User", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="User") FGs2LotteryOwnUser Me(
        FGs2LotteryNamespace Namespace,
        FGs2AccessToken AccessToken
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Lottery::LotteryModel", Category="Game Server Services|GS2-Lottery|Namespace|LotteryModel", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="LotteryModel") FGs2LotteryLotteryModel LotteryModel(
        FGs2LotteryNamespace Namespace,
        FString LotteryName
    );
};