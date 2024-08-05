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

#include "Log/Model/IssueStampSheetLog.h"

namespace Gs2::Log::Model
{
    FIssueStampSheetLog::FIssueStampSheetLog():
        TimestampValue(TOptional<int64>()),
        TransactionIdValue(TOptional<FString>()),
        ServiceValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ActionValue(TOptional<FString>()),
        ArgsValue(TOptional<FString>()),
        TasksValue(nullptr)
    {
    }

    FIssueStampSheetLog::FIssueStampSheetLog(
        const FIssueStampSheetLog& From
    ):
        TimestampValue(From.TimestampValue),
        TransactionIdValue(From.TransactionIdValue),
        ServiceValue(From.ServiceValue),
        MethodValue(From.MethodValue),
        UserIdValue(From.UserIdValue),
        ActionValue(From.ActionValue),
        ArgsValue(From.ArgsValue),
        TasksValue(From.TasksValue)
    {
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithArgs(
        const TOptional<FString> Args
    )
    {
        this->ArgsValue = Args;
        return SharedThis(this);
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::WithTasks(
        const TSharedPtr<TArray<FString>> Tasks
    )
    {
        this->TasksValue = Tasks;
        return SharedThis(this);
    }
    TOptional<int64> FIssueStampSheetLog::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FIssueStampSheetLog::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FIssueStampSheetLog::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<FString> FIssueStampSheetLog::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FIssueStampSheetLog::GetMethod() const
    {
        return MethodValue;
    }
    TOptional<FString> FIssueStampSheetLog::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FIssueStampSheetLog::GetAction() const
    {
        return ActionValue;
    }
    TOptional<FString> FIssueStampSheetLog::GetArgs() const
    {
        return ArgsValue;
    }
    TSharedPtr<TArray<FString>> FIssueStampSheetLog::GetTasks() const
    {
        return TasksValue;
    }

    TSharedPtr<FIssueStampSheetLog> FIssueStampSheetLog::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIssueStampSheetLog>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
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
                }() : TOptional<FString>())
            ->WithTasks(Data->HasField(ANSI_TO_TCHAR("tasks")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    auto v = MakeShared<TArray<FString>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("tasks")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("tasks")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("tasks")))
                        {
                            v->Add(JsonObjectValue->AsString());
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<FString>>());
    }

    TSharedPtr<FJsonObject> FIssueStampSheetLog::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
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
        if (TasksValue != nullptr && TasksValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TasksValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("tasks", v);
        }
        return JsonRootObject;
    }

    FString FIssueStampSheetLog::TypeName = "IssueStampSheetLog";
}