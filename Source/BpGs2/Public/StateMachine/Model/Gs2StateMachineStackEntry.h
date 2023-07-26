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

#include "StateMachine/Model/Gs2StateMachineEzStackEntry.h"
#include "Gs2StateMachineStackEntry.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineStackEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString StateMachineName = "";
    UPROPERTY(BlueprintReadWrite)
    FString TaskName = "";
};

inline FGs2StateMachineStackEntry EzStackEntryToFGs2StateMachineStackEntry(
    const Gs2::UE5::StateMachine::Model::FEzStackEntryPtr Model
)
{
    FGs2StateMachineStackEntry Value;
    Value.StateMachineName = Model->GetStateMachineName() ? *Model->GetStateMachineName() : "";
    Value.TaskName = Model->GetTaskName() ? *Model->GetTaskName() : "";
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzStackEntryPtr FGs2StateMachineStackEntryToEzStackEntry(
    const FGs2StateMachineStackEntry Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzStackEntry>()
        ->WithStateMachineName(Model.StateMachineName)
        ->WithTaskName(Model.TaskName);
}