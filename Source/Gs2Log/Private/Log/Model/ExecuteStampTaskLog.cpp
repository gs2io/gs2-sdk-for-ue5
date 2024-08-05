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

#include "Log/Model/ExecuteStampTaskLog.h"

namespace Gs2::Log::Model
{
    FExecuteStampTaskLog::FExecuteStampTaskLog():
        TimestampValue(TOptional<int64>()),
        TaskIdValue(TOptional<FString>()),
        ServiceValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ActionValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>())
    {
    }

    FExecuteStampTaskLog::FExecuteStampTaskLog(
        const FExecuteStampTaskLog& From
    ):
        TimestampValue(From.TimestampValue),
        TaskIdValue(From.TaskIdValue),
        ServiceValue(From.ServiceValue),
        MethodValue(From.MethodValue),
        UserIdValue(From.UserIdValue),
        ActionValue(From.ActionValue),
        ArgsValue(From.ArgsValue)
    {
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::WithTaskId(
        const TOptional<FString> TaskId
    )
    {
        this->TaskIdValue = TaskId;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }
    TOptional<int64> FExecuteStampTaskLog::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FExecuteStampTaskLog::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FExecuteStampTaskLog::GetTaskId() const
    {
        return TaskIdValue;
    }
    TOptional<FString> FExecuteStampTaskLog::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FExecuteStampTaskLog::GetMethod() const
    {
        return MethodValue;
    }
    TOptional<FString> FExecuteStampTaskLog::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FExecuteStampTaskLog::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FExecuteStampTaskLog::GetArgs() const
    {
        return ArgsValue;
    }

    TSharedPtr<FExecuteStampTaskLog> FExecuteStampTaskLog::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FExecuteStampTaskLog>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithTaskId(Data->HasField(ANSI_TO_TCHAR("taskId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("taskId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithService(Data->HasField(ANSI_TO_TCHAR("service")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("service"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMethod(Data->HasField(ANSI_TO_TCHAR("method")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("method"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAction(Data->HasField(ANSI_TO_TCHAR("action")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("action"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithArgs(Data->HasField(ANSI_TO_TCHAR("args")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("args"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FExecuteStampTaskLog::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (TaskIdValue.IsSet())
        {
            JsonRootObject->SetStringField("taskId", TaskIdValue.GetValue());
        }
        if (ServiceValue.IsSet())
        {
            JsonRootObject->SetStringField("service", ServiceValue.GetValue());
        }
        if (MethodValue.IsSet())
        {
            JsonRootObject->SetStringField("method", MethodValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ActionValue.IsSet())
        {
            JsonRootObject->SetStringField("action", ActionValue.GetValue());
        }
        if (ArgsValue.IsSet())
        {
            JsonRootObject->SetStringField("args", ArgsValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FExecuteStampTaskLog::TypeName = "ExecuteStampTaskLog";
}