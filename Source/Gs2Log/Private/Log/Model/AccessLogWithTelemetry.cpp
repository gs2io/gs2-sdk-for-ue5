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

#include "Log/Model/AccessLogWithTelemetry.h"

namespace Gs2::Log::Model
{
    FAccessLogWithTelemetry::FAccessLogWithTelemetry():
        TimestampValue(TOptional<int64>()),
        SourceRequestIdValue(TOptional<FString>()),
        RequestIdValue(TOptional<FString>()),
        DurationValue(TOptional<int64>()),
        ServiceValue(TOptional<FString>()),
        MethodValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        RequestValue(TOptional<FString>()),
        ResultValue(TOptional<FString>()),
        StatusValue(TOptional<FString>())
    {
    }

    FAccessLogWithTelemetry::FAccessLogWithTelemetry(
        const FAccessLogWithTelemetry& From
    ):
        TimestampValue(From.TimestampValue),
        SourceRequestIdValue(From.SourceRequestIdValue),
        RequestIdValue(From.RequestIdValue),
        DurationValue(From.DurationValue),
        ServiceValue(From.ServiceValue),
        MethodValue(From.MethodValue),
        UserIdValue(From.UserIdValue),
        RequestValue(From.RequestValue),
        ResultValue(From.ResultValue),
        StatusValue(From.StatusValue)
    {
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithSourceRequestId(
        const TOptional<FString> SourceRequestId
    )
    {
        this->SourceRequestIdValue = SourceRequestId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithRequestId(
        const TOptional<FString> RequestId
    )
    {
        this->RequestIdValue = RequestId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithDuration(
        const TOptional<int64> Duration
    )
    {
        this->DurationValue = Duration;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithService(
        const TOptional<FString> Service
    )
    {
        this->ServiceValue = Service;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithMethod(
        const TOptional<FString> Method
    )
    {
        this->MethodValue = Method;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithRequest(
        const TOptional<FString> Request
    )
    {
        this->RequestValue = Request;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithResult(
        const TOptional<FString> Result
    )
    {
        this->ResultValue = Result;
        return SharedThis(this);
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }
    TOptional<int64> FAccessLogWithTelemetry::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FAccessLogWithTelemetry::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FAccessLogWithTelemetry::GetSourceRequestId() const
    {
        return SourceRequestIdValue;
    }
    TOptional<FString> FAccessLogWithTelemetry::GetRequestId() const
    {
        return RequestIdValue;
    }
    TOptional<int64> FAccessLogWithTelemetry::GetDuration() const
    {
        return DurationValue;
    }

    FString FAccessLogWithTelemetry::GetDurationString() const
    {
        if (!DurationValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DurationValue.GetValue());
    }
    TOptional<FString> FAccessLogWithTelemetry::GetService() const
    {
        return ServiceValue;
    }
    TOptional<FString> FAccessLogWithTelemetry::GetMethod() const
    {
        return MethodValue;
    }
    TOptional<FString> FAccessLogWithTelemetry::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FAccessLogWithTelemetry::GetRequest() const
    {
        return RequestValue;
    }
    TOptional<FString> FAccessLogWithTelemetry::GetResult() const
    {
        return ResultValue;
    }
    TOptional<FString> FAccessLogWithTelemetry::GetStatus() const
    {
        return StatusValue;
    }

    TSharedPtr<FAccessLogWithTelemetry> FAccessLogWithTelemetry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAccessLogWithTelemetry>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithSourceRequestId(Data->HasField(ANSI_TO_TCHAR("sourceRequestId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("sourceRequestId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRequestId(Data->HasField(ANSI_TO_TCHAR("requestId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("requestId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDuration(Data->HasField(ANSI_TO_TCHAR("duration")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("duration"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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
                }() : TOptional<FString>())
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("status"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAccessLogWithTelemetry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (SourceRequestIdValue.IsSet())
        {
            JsonRootObject->SetStringField("sourceRequestId", SourceRequestIdValue.GetValue());
        }
        if (RequestIdValue.IsSet())
        {
            JsonRootObject->SetStringField("requestId", RequestIdValue.GetValue());
        }
        if (DurationValue.IsSet())
        {
            JsonRootObject->SetStringField("duration", FString::Printf(TEXT("%lld"), DurationValue.GetValue()));
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
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAccessLogWithTelemetry::TypeName = "AccessLogWithTelemetry";
}