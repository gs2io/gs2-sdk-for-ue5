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

#include "Exchange/Model/Gs2ExchangeEzConfig.h"
#include "Gs2ExchangeConfig.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeConfig
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Key = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Value = "";
};

inline FGs2ExchangeConfig EzConfigToFGs2ExchangeConfig(
    const Gs2::UE5::Exchange::Model::FEzConfigPtr Model
)
{
    FGs2ExchangeConfig Value;
    Value.Key = Model->GetKey() ? *Model->GetKey() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : "";
    return Value;
}

inline Gs2::UE5::Exchange::Model::FEzConfigPtr FGs2ExchangeConfigToEzConfig(
    const FGs2ExchangeConfig Model
)
{
    return MakeShared<Gs2::UE5::Exchange::Model::FEzConfig>()
        ->WithKey(Model.Key)
        ->WithValue(Model.Value);
}