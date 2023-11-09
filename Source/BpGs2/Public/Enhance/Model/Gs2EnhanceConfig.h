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

#include "Enhance/Model/Gs2EnhanceEzConfig.h"
#include "Gs2EnhanceConfig.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceConfig
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Key = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Value = "";
};

inline FGs2EnhanceConfig EzConfigToFGs2EnhanceConfig(
    const Gs2::UE5::Enhance::Model::FEzConfigPtr Model
)
{
    FGs2EnhanceConfig Value;
    Value.Key = Model->GetKey() ? *Model->GetKey() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : "";
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzConfigPtr FGs2EnhanceConfigToEzConfig(
    const FGs2EnhanceConfig Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzConfig>()
        ->WithKey(Model.Key)
        ->WithValue(Model.Value);
}