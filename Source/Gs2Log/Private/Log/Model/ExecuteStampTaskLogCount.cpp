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

#include "Log/Model/ExecuteStampTaskLogCount.h"

namespace Gs2::Log::Model
{
    FExecuteStampTaskLogCount::FExecuteStampTaskLogCount():
        ServiceValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ActionValue(TOptional<FString>()),
        CountValue(TOptional<int64>())
    {
    }

    FExecuteStampTaskLogCount::FExecuteStampTaskLogCount(
        const FExecuteStampTaskLogCount& From
    ):
        ServiceValue(From.ServiceValue),
        MethodValue(From.MethodValue),
        UserIdValue(From.UserIdValue),
        ActionValue(From.ActionValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FExecuteStampTaskLogCount> FExecuteStampTaskLogCount::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLogCount> FExecuteStampTaskLogCount::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLogCount> FExecuteStampTaskLogCount::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLogCount> FExecuteStampTaskLogCount::WithAction(
        const TOptional<FString> Action
    )
    {
        this->ActionValue = Action;
        return SharedThis(this);
    }

    TSharedPtr<FExecuteStampTaskLogCount> FExecuteStampTaskLogCount::WithCount(
        const TOptional<int64> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FExecuteStampTaskLogCount::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FExecuteStampTaskLogCount::GetMethod() const
    {
        return MethodValue;
    }
    TOptional<FString> FExecuteStampTaskLogCount::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FExecuteStampTaskLogCount::GetAction() const
    {
        return ActionValue;
    }
    TOptional<int64> FExecuteStampTaskLogCount::GetCount() const
    {
        return CountValue;
    }

    FString FExecuteStampTaskLogCount::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CountValue.GetValue());
    }

    TSharedPtr<FExecuteStampTaskLogCount> FExecuteStampTaskLogCount::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FExecuteStampTaskLogCount>()
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
            ->WithCount(Data->HasField(ANSI_TO_TCHAR("count")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("count"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FExecuteStampTaskLogCount::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
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
        if (CountValue.IsSet())
        {
            JsonRootObject->SetStringField("count", FString::Printf(TEXT("%lld"), CountValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FExecuteStampTaskLogCount::TypeName = "ExecuteStampTaskLogCount";
}