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

#include "StateMachine/Model/StackEntry.h"

namespace Gs2::StateMachine::Model
{
    FStackEntry::FStackEntry():
        StateMachineNameValue(TOptional<FString>()),
        TaskNameValue(TOptional<FString>())
    {
    }

    FStackEntry::FStackEntry(
        const FStackEntry& From
    ):
        StateMachineNameValue(From.StateMachineNameValue),
        TaskNameValue(From.TaskNameValue)
    {
    }

    TSharedPtr<FStackEntry> FStackEntry::WithStateMachineName(
        const TOptional<FString> StateMachineName
    )
    {
        this->StateMachineNameValue = StateMachineName;
        return SharedThis(this);
    }

    TSharedPtr<FStackEntry> FStackEntry::WithTaskName(
        const TOptional<FString> TaskName
    )
    {
        this->TaskNameValue = TaskName;
        return SharedThis(this);
    }
    TOptional<FString> FStackEntry::GetStateMachineName() const
    {
        return StateMachineNameValue;
    }
    TOptional<FString> FStackEntry::GetTaskName() const
    {
        return TaskNameValue;
    }

    TSharedPtr<FStackEntry> FStackEntry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FStackEntry>()
            ->WithStateMachineName(Data->HasField("stateMachineName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("stateMachineName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTaskName(Data->HasField("taskName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("taskName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FStackEntry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (StateMachineNameValue.IsSet())
        {
            JsonRootObject->SetStringField("stateMachineName", StateMachineNameValue.GetValue());
        }
        if (TaskNameValue.IsSet())
        {
            JsonRootObject->SetStringField("taskName", TaskNameValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FStackEntry::TypeName = "StackEntry";
}