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

#include "StateMachine/Model/Gs2StateMachineEzEmitEvent.h"

namespace Gs2::UE5::StateMachine::Model
{

    TSharedPtr<FEzEmitEvent> FEzEmitEvent::WithEvent(
        const TOptional<FString> Event
    )
    {
        this->EventValue = Event;
        return SharedThis(this);
    }

    TSharedPtr<FEzEmitEvent> FEzEmitEvent::WithParameters(
        const TOptional<FString> Parameters
    )
    {
        this->ParametersValue = Parameters;
        return SharedThis(this);
    }

    TSharedPtr<FEzEmitEvent> FEzEmitEvent::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }
    TOptional<FString> FEzEmitEvent::GetEvent() const
    {
        return EventValue;
    }
    TOptional<FString> FEzEmitEvent::GetParameters() const
    {
        return ParametersValue;
    }
    TOptional<int64> FEzEmitEvent::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FEzEmitEvent::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }

    Gs2::StateMachine::Model::FEmitEventPtr FEzEmitEvent::ToModel() const
    {
        return MakeShared<Gs2::StateMachine::Model::FEmitEvent>()
            ->WithEvent(EventValue)
            ->WithParameters(ParametersValue)
            ->WithTimestamp(TimestampValue);
    }

    TSharedPtr<FEzEmitEvent> FEzEmitEvent::FromModel(const Gs2::StateMachine::Model::FEmitEventPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzEmitEvent>()
            ->WithEvent(Model->GetEvent())
            ->WithParameters(Model->GetParameters())
            ->WithTimestamp(Model->GetTimestamp());
    }
}