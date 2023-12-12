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

#include "StateMachine/Model/Gs2StateMachineEzRandomStatus.h"
#include "StateMachine/Model/Gs2StateMachineRandomUsed.h"
#include "Gs2StateMachineRandomStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineRandomStatus
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 Seed = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2StateMachineRandomUsed> Used = TArray<FGs2StateMachineRandomUsed>();
};

inline FGs2StateMachineRandomStatus EzRandomStatusToFGs2StateMachineRandomStatus(
    const Gs2::UE5::StateMachine::Model::FEzRandomStatusPtr Model
)
{
    FGs2StateMachineRandomStatus Value;
    Value.Seed = Model->GetSeed() ? *Model->GetSeed() : 0;
    Value.Used = Model->GetUsed() ? [&]
    {
        TArray<FGs2StateMachineRandomUsed> r;
        for (auto v : *Model->GetUsed())
        {r.Add(EzRandomUsedToFGs2StateMachineRandomUsed(v));
        }
        return r;
    }() : TArray<FGs2StateMachineRandomUsed>();
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzRandomStatusPtr FGs2StateMachineRandomStatusToEzRandomStatus(
    const FGs2StateMachineRandomStatus Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzRandomStatus>()
        ->WithSeed(Model.Seed)
        ->WithUsed([&]{
            auto r = MakeShared<TArray<Gs2::UE5::StateMachine::Model::FEzRandomUsedPtr>>();
            for (auto v : Model.Used) {
                r->Add(FGs2StateMachineRandomUsedToEzRandomUsed(v));
            }
            return r;
        }());
}