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

#include "Enchant/Model/Gs2EnchantEzRarityParameterCountModel.h"
#include "Gs2EnchantRarityParameterCountModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantRarityParameterCountModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Count = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Weight = 0;
};

inline FGs2EnchantRarityParameterCountModel EzRarityParameterCountModelToFGs2EnchantRarityParameterCountModel(
    const Gs2::UE5::Enchant::Model::FEzRarityParameterCountModelPtr Model
)
{
    FGs2EnchantRarityParameterCountModel Value;
    Value.Count = Model->GetCount() ? *Model->GetCount() : 0;
    Value.Weight = Model->GetWeight() ? *Model->GetWeight() : 0;
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzRarityParameterCountModelPtr FGs2EnchantRarityParameterCountModelToEzRarityParameterCountModel(
    const FGs2EnchantRarityParameterCountModel Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzRarityParameterCountModel>()
        ->WithCount(Model.Count)
        ->WithWeight(Model.Weight);
}