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

#include "Enchant/Model/Gs2EnchantEzRarityParameterValue.h"
#include "Gs2EnchantRarityParameterValue.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantRarityParameterValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ResourceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 ResourceValue = 0;
};

inline FGs2EnchantRarityParameterValue EzRarityParameterValueToFGs2EnchantRarityParameterValue(
    const Gs2::UE5::Enchant::Model::FEzRarityParameterValuePtr Model
)
{
    FGs2EnchantRarityParameterValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.ResourceName = Model->GetResourceName() ? *Model->GetResourceName() : "";
    Value.ResourceValue = Model->GetResourceValue() ? *Model->GetResourceValue() : 0;
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzRarityParameterValuePtr FGs2EnchantRarityParameterValueToEzRarityParameterValue(
    const FGs2EnchantRarityParameterValue Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzRarityParameterValue>()
        ->WithName(Model.Name)
        ->WithResourceName(Model.ResourceName)
        ->WithResourceValue(Model.ResourceValue);
}