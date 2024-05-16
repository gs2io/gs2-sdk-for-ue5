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

#include "StateMachine/Model/Variable.h"

namespace Gs2::StateMachine::Model
{
    FVariable::FVariable():
        StateMachineNameValue(TOptional<FString>()),
        ValueValue(TOptional<FString>())
    {
    }

    FVariable::FVariable(
        const FVariable& From
    ):
        StateMachineNameValue(From.StateMachineNameValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FVariable> FVariable::WithStateMachineName(
        const TOptional<FString> StateMachineName
    )
    {
        this->StateMachineNameValue = StateMachineName;
        return SharedThis(this);
    }

    TSharedPtr<FVariable> FVariable::WithValue(
        const TOptional<FString> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FVariable::GetStateMachineName() const
    {
        return StateMachineNameValue;
    }
    TOptional<FString> FVariable::GetValue() const
    {
        return ValueValue;
    }

    TSharedPtr<FVariable> FVariable::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVariable>()
            ->WithStateMachineName(Data->HasField(ANSI_TO_TCHAR("stateMachineName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("stateMachineName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("value"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVariable::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StateMachineNameValue.IsSet())
        {
            JsonRootObject->SetStringField("stateMachineName", StateMachineNameValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetStringField("value", ValueValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FVariable::TypeName = "Variable";
}