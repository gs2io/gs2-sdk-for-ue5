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

#include "StateMachine/Model/Gs2StateMachineEzEvent.h"
#include "StateMachine/Model/Gs2StateMachineChangeStateEvent.h"
#include "StateMachine/Model/Gs2StateMachineEmitEvent.h"
#include "Gs2StateMachineEvent.generated.h"

USTRUCT(BlueprintType)
struct FGs2StateMachineEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString EventType = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FGs2StateMachineChangeStateEvent ChangeStateEvent = FGs2StateMachineChangeStateEvent();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FGs2StateMachineEmitEvent EmitEvent = FGs2StateMachineEmitEvent();
};

inline FGs2StateMachineEvent EzEventToFGs2StateMachineEvent(
    const Gs2::UE5::StateMachine::Model::FEzEventPtr Model
)
{
    FGs2StateMachineEvent Value;
    Value.EventType = Model->GetEventType() ? *Model->GetEventType() : "";
    Value.ChangeStateEvent = Model->GetChangeStateEvent() ? EzChangeStateEventToFGs2StateMachineChangeStateEvent(Model->GetChangeStateEvent()) : FGs2StateMachineChangeStateEvent();
    Value.EmitEvent = Model->GetEmitEvent() ? EzEmitEventToFGs2StateMachineEmitEvent(Model->GetEmitEvent()) : FGs2StateMachineEmitEvent();
    return Value;
}

inline Gs2::UE5::StateMachine::Model::FEzEventPtr FGs2StateMachineEventToEzEvent(
    const FGs2StateMachineEvent Model
)
{
    return MakeShared<Gs2::UE5::StateMachine::Model::FEzEvent>()
        ->WithEventType(Model.EventType)
        ->WithChangeStateEvent(FGs2StateMachineChangeStateEventToEzChangeStateEvent(Model.ChangeStateEvent))
        ->WithEmitEvent(FGs2StateMachineEmitEventToEzEmitEvent(Model.EmitEvent));
}