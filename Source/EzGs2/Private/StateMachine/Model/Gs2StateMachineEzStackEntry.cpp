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

#include "EzGs2/Public/StateMachine/Model/Gs2StateMachineEzStackEntry.h"

namespace Gs2::UE5::StateMachine::Model
{

    TSharedPtr<FEzStackEntry> FEzStackEntry::WithStateMachineName(
        const TOptional<FString> StateMachineName
    )
    {
        this->StateMachineNameValue = StateMachineName;
        return SharedThis(this);
    }

    TSharedPtr<FEzStackEntry> FEzStackEntry::WithTaskName(
        const TOptional<FString> TaskName
    )
    {
        this->TaskNameValue = TaskName;
        return SharedThis(this);
    }
    TOptional<FString> FEzStackEntry::GetStateMachineName() const
    {
        return StateMachineNameValue;
    }
    TOptional<FString> FEzStackEntry::GetTaskName() const
    {
        return TaskNameValue;
    }

    Gs2::StateMachine::Model::FStackEntryPtr FEzStackEntry::ToModel() const
    {
        return MakeShared<Gs2::StateMachine::Model::FStackEntry>()
            ->WithStateMachineName(StateMachineNameValue)
            ->WithTaskName(TaskNameValue);
    }

    TSharedPtr<FEzStackEntry> FEzStackEntry::FromModel(const Gs2::StateMachine::Model::FStackEntryPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzStackEntry>()
            ->WithStateMachineName(Model->GetStateMachineName())
            ->WithTaskName(Model->GetTaskName());
    }
}