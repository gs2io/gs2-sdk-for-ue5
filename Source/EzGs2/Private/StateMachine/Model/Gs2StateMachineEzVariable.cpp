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

#include "StateMachine/Model/Gs2StateMachineEzVariable.h"

namespace Gs2::UE5::StateMachine::Model
{

    TSharedPtr<FEzVariable> FEzVariable::WithStateMachineName(
        const TOptional<FString> StateMachineName
    )
    {
        this->StateMachineNameValue = StateMachineName;
        return SharedThis(this);
    }

    TSharedPtr<FEzVariable> FEzVariable::WithValue(
        const TOptional<FString> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FEzVariable::GetStateMachineName() const
    {
        return StateMachineNameValue;
    }
    TOptional<FString> FEzVariable::GetValue() const
    {
        return ValueValue;
    }

    Gs2::StateMachine::Model::FVariablePtr FEzVariable::ToModel() const
    {
        return MakeShared<Gs2::StateMachine::Model::FVariable>()
            ->WithStateMachineName(StateMachineNameValue)
            ->WithValue(ValueValue);
    }

    TSharedPtr<FEzVariable> FEzVariable::FromModel(const Gs2::StateMachine::Model::FVariablePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzVariable>()
            ->WithStateMachineName(Model->GetStateMachineName())
            ->WithValue(Model->GetValue());
    }
}