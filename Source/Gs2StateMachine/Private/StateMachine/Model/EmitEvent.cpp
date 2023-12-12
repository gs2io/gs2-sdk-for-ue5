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

#include "StateMachine/Model/EmitEvent.h"

namespace Gs2::StateMachine::Model
{
    FEmitEvent::FEmitEvent():
        EventValue(TOptional<FString>()),
        ParametersValue(TOptional<FString>()),
        TimestampValue(TOptional<int64>())
    {
    }

    FEmitEvent::FEmitEvent(
        const FEmitEvent& From
    ):
        EventValue(From.EventValue),
        ParametersValue(From.ParametersValue),
        TimestampValue(From.TimestampValue)
    {
    }

    TSharedPtr<FEmitEvent> FEmitEvent::WithEvent(
        const TOptional<FString> Event
    )
    {
        this->EventValue = Event;
        return SharedThis(this);
    }

    TSharedPtr<FEmitEvent> FEmitEvent::WithParameters(
        const TOptional<FString> Parameters
    )
    {
        this->ParametersValue = Parameters;
        return SharedThis(this);
    }

    TSharedPtr<FEmitEvent> FEmitEvent::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }
    TOptional<FString> FEmitEvent::GetEvent() const
    {
        return EventValue;
    }
    TOptional<FString> FEmitEvent::GetParameters() const
    {
        return ParametersValue;
    }
    TOptional<int64> FEmitEvent::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FEmitEvent::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }

    TSharedPtr<FEmitEvent> FEmitEvent::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEmitEvent>()
            ->WithEvent(Data->HasField("event") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("event", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithParameters(Data->HasField("parameters") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("parameters", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTimestamp(Data->HasField("timestamp") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("timestamp", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FEmitEvent::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (EventValue.IsSet())
        {
            JsonRootObject->SetStringField("event", EventValue.GetValue());
        }
        if (ParametersValue.IsSet())
        {
            JsonRootObject->SetStringField("parameters", ParametersValue.GetValue());
        }
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FEmitEvent::TypeName = "EmitEvent";
}