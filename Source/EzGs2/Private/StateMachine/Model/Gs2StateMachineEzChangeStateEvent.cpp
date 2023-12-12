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

#include "StateMachine/Model/Gs2StateMachineEzChangeStateEvent.h"

namespace Gs2::UE5::StateMachine::Model
{

    TSharedPtr<FEzChangeStateEvent> FEzChangeStateEvent::WithTaskName(
        const TOptional<FString> TaskName
    )
    {
        this->TaskNameValue = TaskName;
        return SharedThis(this);
    }

    TSharedPtr<FEzChangeStateEvent> FEzChangeStateEvent::WithHash(
        const TOptional<FString> Hash
    )
    {
        this->HashValue = Hash;
        return SharedThis(this);
    }

    TSharedPtr<FEzChangeStateEvent> FEzChangeStateEvent::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }
    TOptional<FString> FEzChangeStateEvent::GetTaskName() const
    {
        return TaskNameValue;
    }
    TOptional<FString> FEzChangeStateEvent::GetHash() const
    {
        return HashValue;
    }
    TOptional<int64> FEzChangeStateEvent::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FEzChangeStateEvent::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }

    Gs2::StateMachine::Model::FChangeStateEventPtr FEzChangeStateEvent::ToModel() const
    {
        return MakeShared<Gs2::StateMachine::Model::FChangeStateEvent>()
            ->WithTaskName(TaskNameValue)
            ->WithHash(HashValue)
            ->WithTimestamp(TimestampValue);
    }

    TSharedPtr<FEzChangeStateEvent> FEzChangeStateEvent::FromModel(const Gs2::StateMachine::Model::FChangeStateEventPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzChangeStateEvent>()
            ->WithTaskName(Model->GetTaskName())
            ->WithHash(Model->GetHash())
            ->WithTimestamp(Model->GetTimestamp());
    }
}