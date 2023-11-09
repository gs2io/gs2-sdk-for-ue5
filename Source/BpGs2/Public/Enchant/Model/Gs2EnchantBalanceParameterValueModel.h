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

#include "Enchant/Model/Gs2EnchantEzBalanceParameterValueModel.h"
#include "Gs2EnchantBalanceParameterValueModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantBalanceParameterValueModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
};

inline FGs2EnchantBalanceParameterValueModel EzBalanceParameterValueModelToFGs2EnchantBalanceParameterValueModel(
    const Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModelPtr Model
)
{
    FGs2EnchantBalanceParameterValueModel Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModelPtr FGs2EnchantBalanceParameterValueModelToEzBalanceParameterValueModel(
    const FGs2EnchantBalanceParameterValueModel Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata);
}