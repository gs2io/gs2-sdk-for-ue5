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

#include "StateMachine/Model/Gs2StateMachineEzVariable.h"
#include "Gs2StateMachineVariable.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineVariable
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString StateMachineName = "";
    UPROPERTY(BlueprintReadWrite)
    FString Value = "";
};

inline FGs2StateMachineVariable EzVariableToFGs2StateMachineVariable(
    const Gs2::UE5::StateMachine::Model::FEzVariablePtr Model
)
{
    FGs2StateMachineVariable Value;
    Value.StateMachineName = Model->GetStateMachineName() ? *Model->GetStateMachineName() : "";
    Value.Value = Model->GetValue() ? *Model->GetValue() : "";
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzVariablePtr FGs2StateMachineVariableToEzVariable(
    const FGs2StateMachineVariable Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzVariable>()
        ->WithStateMachineName(Model.StateMachineName)
        ->WithValue(Model.Value);
}