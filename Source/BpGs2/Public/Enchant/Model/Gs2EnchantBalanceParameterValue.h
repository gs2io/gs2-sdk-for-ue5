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

#include "Enchant/Model/Gs2EnchantEzBalanceParameterValue.h"
#include "Gs2EnchantBalanceParameterValue.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantBalanceParameterValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    int64 Value = 0;
};

inline FGs2EnchantBalanceParameterValue EzBalanceParameterValueToFGs2EnchantBalanceParameterValue(
    const Gs2::UE5::Enchant::Model::FEzBalanceParameterValuePtr Model
)
{
    FGs2EnchantBalanceParameterValue Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : 0;
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzBalanceParameterValuePtr FGs2EnchantBalanceParameterValueToEzBalanceParameterValue(
    const FGs2EnchantBalanceParameterValue Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzBalanceParameterValue>()
        ->WithName(Model.Name)
        ->WithValue(Model.Value);
}