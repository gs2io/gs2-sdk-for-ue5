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

#include "StateMachine/Model/Gs2StateMachineEzEmitEvent.h"
#include "Gs2StateMachineEmitEvent.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineEmitEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Event = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Parameters = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 Timestamp = 0;
};

inline FGs2StateMachineEmitEvent EzEmitEventToFGs2StateMachineEmitEvent(
    const Gs2::UE5::StateMachine::Model::FEzEmitEventPtr Model
)
{
    FGs2StateMachineEmitEvent Value;
    Value.Event = Model->GetEvent() ? *Model->GetEvent() : "";
    Value.Parameters = Model->GetParameters() ? *Model->GetParameters() : "";
    Value.Timestamp = Model->GetTimestamp() ? *Model->GetTimestamp() : 0;
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzEmitEventPtr FGs2StateMachineEmitEventToEzEmitEvent(
    const FGs2StateMachineEmitEvent Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzEmitEvent>()
        ->WithEvent(Model.Event)
        ->WithParameters(Model.Parameters)
        ->WithTimestamp(Model.Timestamp);
}