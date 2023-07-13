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

#include "LoginReward/Model/Gs2LoginRewardEzConfig.h"
#include "Gs2LoginRewardConfig.generated.h"

USTRUCT(BlueprintType)
struct FGs2LoginRewardConfig
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Key = "";
    UPROPERTY(BlueprintReadWrite)
    FString Value = "";
};

inline FGs2LoginRewardConfig EzConfigToFGs2LoginRewardConfig(
    const Gs2::UE5::LoginReward::Model::FEzConfigPtr Model
)
{
    FGs2LoginRewardConfig Value;
    Value.Key = Model->GetKey() ? *Model->GetKey() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : "";
    return Value;
}

inline Gs2::UE5::LoginReward::Model::FEzConfigPtr FGs2LoginRewardConfigToEzConfig(
    const FGs2LoginRewardConfig Model
)
{
    return MakeShared<Gs2::UE5::LoginReward::Model::FEzConfig>()
        ->WithKey(Model.Key)
        ->WithValue(Model.Value);
}