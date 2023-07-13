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

#include "LoginReward/Model/Gs2LoginRewardEzReward.h"
#include "LoginReward/Model/Gs2LoginRewardAcquireAction.h"
#include "Gs2LoginRewardReward.generated.h"

USTRUCT(BlueprintType)
struct FGs2LoginRewardReward
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TArray<FGs2LoginRewardAcquireAction> AcquireActions = TArray<FGs2LoginRewardAcquireAction>();
};

inline FGs2LoginRewardReward EzRewardToFGs2LoginRewardReward(
    const Gs2::UE5::LoginReward::Model::FEzRewardPtr Model
)
{
    FGs2LoginRewardReward Value;
    Value.AcquireActions = Model->GetAcquireActions() ? [&]
    {
        TArray<FGs2LoginRewardAcquireAction> r;
        for (auto v : *Model->GetAcquireActions())
        {r.Add(EzAcquireActionToFGs2LoginRewardAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2LoginRewardAcquireAction>();
    return Value;
}

inline Gs2::UE5::LoginReward::Model::FEzRewardPtr FGs2LoginRewardRewardToEzReward(
    const FGs2LoginRewardReward Model
)
{
    return MakeShared<Gs2::UE5::LoginReward::Model::FEzReward>()
        ->WithAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::LoginReward::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.AcquireActions) {
                r->Add(FGs2LoginRewardAcquireActionToEzAcquireAction(v));
            }
            return r;
        }());
}