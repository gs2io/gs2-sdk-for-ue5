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

#include "Log/Model/AccessLog.h"

namespace Gs2::Log::Model
{
    FAccessLog::FAccessLog():
        TimestampValue(TOptional<int64>()),
        RequestIdValue(TOptional<FString>()),
        ServiceValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RequestValue(TOptional<FString>()),
        ResultValue(TOptional<FString>())
    {
    }

    FAccessLog::FAccessLog(
        const FAccessLog& From
    ):
        TimestampValue(From.TimestampValue),
        RequestIdValue(From.RequestIdValue),
        ServiceValue(From.ServiceValue),
        MethodValue(From.MethodValue),
        UserIdValue(From.UserIdValue),
        RequestValue(From.RequestValue),
        ResultValue(From.ResultValue)
    {
    }

    TSharedPtr<FAccessLog> FAccessLog::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLog> FAccessLog::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLog> FAccessLog::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLog> FAccessLog::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLog> FAccessLog::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLog> FAccessLog::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLog> FAccessLog::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }
    TOptional<int64> FAccessLog::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FAccessLog::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FAccessLog::GetRequestId() const
    {
        return RequestIdValue;
    }
    TOptional<FString> FAccessLog::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FAccessLog::GetMethod() const
    {
        return MethodValue;
    }
    TOptional<FString> FAccessLog::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FAccessLog::GetRequest() const
    {
        return RequestValue;
    }
    TOptional<FString> FAccessLog::GetResult() const
    {
        return ResultValue;
    }

    TSharedPtr<FAccessLog> FAccessLog::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAccessLog>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRequestId(Data->HasField(ANSI_TO_TCHAR("requestId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("requestId"), v))
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
            ->WithRequest(Data->HasField(ANSI_TO_TCHAR("request")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("request"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithResult(Data->HasField(ANSI_TO_TCHAR("result")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("result"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAccessLog::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (RequestIdValue.IsSet())
        {
            JsonRootObject->SetStringField("requestId", RequestIdValue.GetValue());
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
        if (RequestValue.IsSet())
        {
            JsonRootObject->SetStringField("request", RequestValue.GetValue());
        }
        if (ResultValue.IsSet())
        {
            JsonRootObject->SetStringField("result", ResultValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAccessLog::TypeName = "AccessLog";
}