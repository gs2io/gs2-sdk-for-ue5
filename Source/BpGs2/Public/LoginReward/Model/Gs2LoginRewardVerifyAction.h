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

#include "LoginReward/Model/Gs2LoginRewardEzVerifyAction.h"
#include "Gs2LoginRewardVerifyAction.generated.h"

USTRUCT(BlueprintType)
struct FGs2LoginRewardVerifyAction
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Request = "";
};

inline FGs2LoginRewardVerifyAction EzVerifyActionToFGs2LoginRewardVerifyAction(
    const Gs2::UE5::LoginReward::Model::FEzVerifyActionPtr Model
)
{
    FGs2LoginRewardVerifyAction Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.Request = Model->GetRequest() ? *Model->GetRequest() : "";
    return Value;
}

inline Gs2::UE5::LoginReward::Model::FEzVerifyActionPtr FGs2LoginRewardVerifyActionToEzVerifyAction(
    const FGs2LoginRewardVerifyAction Model
)
{
    return MakeShared<Gs2::UE5::LoginReward::Model::FEzVerifyAction>()
        ->WithAction(Model.Action)
        ->WithRequest(Model.Request);
}