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

#include "LoginReward/Model/Gs2LoginRewardEzAcquireAction.h"
#include "Gs2LoginRewardAcquireAction.generated.h"

USTRUCT(BlueprintType)
struct FGs2LoginRewardAcquireAction
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(BlueprintReadWrite)
    FString Request = "";
};

inline FGs2LoginRewardAcquireAction EzAcquireActionToFGs2LoginRewardAcquireAction(
    const Gs2::UE5::LoginReward::Model::FEzAcquireActionPtr Model
)
{
    FGs2LoginRewardAcquireAction Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.Request = Model->GetRequest() ? *Model->GetRequest() : "";
    return Value;
}

inline Gs2::UE5::LoginReward::Model::FEzAcquireActionPtr FGs2LoginRewardAcquireActionToEzAcquireAction(
    const FGs2LoginRewardAcquireAction Model
)
{
    return MakeShared<Gs2::UE5::LoginReward::Model::FEzAcquireAction>()
        ->WithAction(Model.Action)
        ->WithRequest(Model.Request);
}