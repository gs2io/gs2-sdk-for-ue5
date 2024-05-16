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

#include "StateMachine/Model/ChangeStateEvent.h"

namespace Gs2::StateMachine::Model
{
    FChangeStateEvent::FChangeStateEvent():
        TaskNameValue(TOptional<FString>()),
        HashValue(TOptional<FString>()),
        TimestampValue(TOptional<int64>())
    {
    }

    FChangeStateEvent::FChangeStateEvent(
        const FChangeStateEvent& From
    ):
        TaskNameValue(From.TaskNameValue),
        HashValue(From.HashValue),
        TimestampValue(From.TimestampValue)
    {
    }

    TSharedPtr<FChangeStateEvent> FChangeStateEvent::WithTaskName(
        const TOptional<FString> TaskName
    )
    {
        this->TaskNameValue = TaskName;
        return SharedThis(this);
    }

    TSharedPtr<FChangeStateEvent> FChangeStateEvent::WithHash(
        const TOptional<FString> Hash
    )
    {
        this->HashValue = Hash;
        return SharedThis(this);
    }

    TSharedPtr<FChangeStateEvent> FChangeStateEvent::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }
    TOptional<FString> FChangeStateEvent::GetTaskName() const
    {
        return TaskNameValue;
    }
    TOptional<FString> FChangeStateEvent::GetHash() const
    {
        return HashValue;
    }
    TOptional<int64> FChangeStateEvent::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FChangeStateEvent::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }

    TSharedPtr<FChangeStateEvent> FChangeStateEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FChangeStateEvent>()
            ->WithTaskName(Data->HasField(ANSI_TO_TCHAR("taskName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("taskName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithHash(Data->HasField(ANSI_TO_TCHAR("hash")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("hash"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FChangeStateEvent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TaskNameValue.IsSet())
        {
            JsonRootObject->SetStringField("taskName", TaskNameValue.GetValue());
        }
        if (HashValue.IsSet())
        {
            JsonRootObject->SetStringField("hash", HashValue.GetValue());
        }
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FChangeStateEvent::TypeName = "ChangeStateEvent";
}