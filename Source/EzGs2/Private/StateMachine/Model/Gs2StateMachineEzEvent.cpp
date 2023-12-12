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

#include "StateMachine/Model/Gs2StateMachineEzEvent.h"

namespace Gs2::UE5::StateMachine::Model
{

    TSharedPtr<FEzEvent> FEzEvent::WithEventType(
        const TOptional<FString> EventType
    )
    {
        this->EventTypeValue = EventType;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithChangeStateEvent(
        const TSharedPtr<Gs2::UE5::StateMachine::Model::FEzChangeStateEvent> ChangeStateEvent
    )
    {
        this->ChangeStateEventValue = ChangeStateEvent;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithEmitEvent(
        const TSharedPtr<Gs2::UE5::StateMachine::Model::FEzEmitEvent> EmitEvent
    )
    {
        this->EmitEventValue = EmitEvent;
        return SharedThis(this);
    }
    TOptional<FString> FEzEvent::GetEventType() const
    {
        return EventTypeValue;
    }
    TSharedPtr<Gs2::UE5::StateMachine::Model::FEzChangeStateEvent> FEzEvent::GetChangeStateEvent() const
    {
        return ChangeStateEventValue;
    }
    TSharedPtr<Gs2::UE5::StateMachine::Model::FEzEmitEvent> FEzEvent::GetEmitEvent() const
    {
        return EmitEventValue;
    }

    Gs2::StateMachine::Model::FEventPtr FEzEvent::ToModel() const
    {
        return MakeShared<Gs2::StateMachine::Model::FEvent>()
            ->WithEventType(EventTypeValue)
            ->WithChangeStateEvent(ChangeStateEventValue == nullptr ? nullptr : ChangeStateEventValue->ToModel())
            ->WithEmitEvent(EmitEventValue == nullptr ? nullptr : EmitEventValue->ToModel());
    }

    TSharedPtr<FEzEvent> FEzEvent::FromModel(const Gs2::StateMachine::Model::FEventPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzEvent>()
            ->WithEventType(Model->GetEventType())
            ->WithChangeStateEvent(Model->GetChangeStateEvent() != nullptr ? Gs2::UE5::StateMachine::Model::FEzChangeStateEvent::FromModel(Model->GetChangeStateEvent()) : nullptr)
            ->WithEmitEvent(Model->GetEmitEvent() != nullptr ? Gs2::UE5::StateMachine::Model::FEzEmitEvent::FromModel(Model->GetEmitEvent()) : nullptr);
    }
}