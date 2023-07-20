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

#include "Enchant/Model/Gs2EnchantEzRarityParameterValueModel.h"
#include "Gs2EnchantRarityParameterValueModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantRarityParameterValueModel
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(BlueprintReadWrite)
    FString ResourceName = "";
    UPROPERTY(BlueprintReadWrite)
    int64 ResourceValue = 0;
    UPROPERTY(BlueprintReadWrite)
    int32 Weight = 0;
};

inline FGs2EnchantRarityParameterValueModel EzRarityParameterValueModelToFGs2EnchantRarityParameterValueModel(
    const Gs2::UE5::Enchant::Model::FEzRarityParameterValueModelPtr Model
)
{
    FGs2EnchantRarityParameterValueModel Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ResourceName = Model->GetResourceName() ? *Model->GetResourceName() : "";
    Value.ResourceValue = Model->GetResourceValue() ? *Model->GetResourceValue() : 0;
    Value.Weight = Model->GetWeight() ? *Model->GetWeight() : 0;
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzRarityParameterValueModelPtr FGs2EnchantRarityParameterValueModelToEzRarityParameterValueModel(
    const FGs2EnchantRarityParameterValueModel Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzRarityParameterValueModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithResourceName(Model.ResourceName)
        ->WithResourceValue(Model.ResourceValue)
        ->WithWeight(Model.Weight);
}