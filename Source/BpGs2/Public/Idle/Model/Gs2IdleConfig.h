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

#include "Idle/Model/Gs2IdleEzConfig.h"
#include "Gs2IdleConfig.generated.h"

USTRUCT(BlueprintType)
struct FGs2IdleConfig
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Key = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Value = "";
};

inline FGs2IdleConfig EzConfigToFGs2IdleConfig(
    const Gs2::UE5::Idle::Model::FEzConfigPtr Model
)
{
    FGs2IdleConfig Value;
    Value.Key = Model->GetKey() ? *Model->GetKey() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : "";
    return Value;
}

inline Gs2::UE5::Idle::Model::FEzConfigPtr FGs2IdleConfigToEzConfig(
    const FGs2IdleConfig Model
)
{
    return MakeShared<Gs2::UE5::Idle::Model::FEzConfig>()
        ->WithKey(Model.Key)
        ->WithValue(Model.Value);
}