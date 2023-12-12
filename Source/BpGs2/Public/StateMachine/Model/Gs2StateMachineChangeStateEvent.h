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

#include "StateMachine/Model/Gs2StateMachineEzChangeStateEvent.h"
#include "Gs2StateMachineChangeStateEvent.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineChangeStateEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TaskName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Hash = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 Timestamp = 0;
};

inline FGs2StateMachineChangeStateEvent EzChangeStateEventToFGs2StateMachineChangeStateEvent(
    const Gs2::UE5::StateMachine::Model::FEzChangeStateEventPtr Model
)
{
    FGs2StateMachineChangeStateEvent Value;
    Value.TaskName = Model->GetTaskName() ? *Model->GetTaskName() : "";
    Value.Hash = Model->GetHash() ? *Model->GetHash() : "";
    Value.Timestamp = Model->GetTimestamp() ? *Model->GetTimestamp() : 0;
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzChangeStateEventPtr FGs2StateMachineChangeStateEventToEzChangeStateEvent(
    const FGs2StateMachineChangeStateEvent Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzChangeStateEvent>()
        ->WithTaskName(Model.TaskName)
        ->WithHash(Model.Hash)
        ->WithTimestamp(Model.Timestamp);
}