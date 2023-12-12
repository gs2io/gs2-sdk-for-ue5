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

#include "StateMachine/Model/Gs2StateMachineEzRandomUsed.h"
#include "Gs2StateMachineRandomUsed.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineRandomUsed
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 Category = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 Used = 0;
};

inline FGs2StateMachineRandomUsed EzRandomUsedToFGs2StateMachineRandomUsed(
    const Gs2::UE5::StateMachine::Model::FEzRandomUsedPtr Model
)
{
    FGs2StateMachineRandomUsed Value;
    Value.Category = Model->GetCategory() ? *Model->GetCategory() : 0;
    Value.Used = Model->GetUsed() ? *Model->GetUsed() : 0;
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzRandomUsedPtr FGs2StateMachineRandomUsedToEzRandomUsed(
    const FGs2StateMachineRandomUsed Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzRandomUsed>()
        ->WithCategory(Model.Category)
        ->WithUsed(Model.Used);
}