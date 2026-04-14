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

#include "Log/Model/TimeseriesValue.h"

namespace Gs2::Log::Model
{
    FTimeseriesValue::FTimeseriesValue():
        KeyValue(TOptional<FString>()),
        ValueValue(TOptional<double>())
    {
    }

    FTimeseriesValue::FTimeseriesValue(
        const FTimeseriesValue& From
    ):
        KeyValue(From.KeyValue),
        ValueValue(From.ValueValue)
    {
    }

    TSharedPtr<FTimeseriesValue> FTimeseriesValue::WithKey(
        const TOptional<FString> Key
    )
    {
        this->KeyValue = Key;
        return SharedThis(this);
    }

    TSharedPtr<FTimeseriesValue> FTimeseriesValue::WithValue(
        const TOptional<double> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }
    TOptional<FString> FTimeseriesValue::GetKey() const
    {
        return KeyValue;
    }
    TOptional<double> FTimeseriesValue::GetValue() const
    {
        return ValueValue;
    }

    FString FTimeseriesValue::GetValueString() const
    {
        if (!ValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), ValueValue.GetValue());
    }

    TSharedPtr<FTimeseriesValue> FTimeseriesValue::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTimeseriesValue>()
            ->WithKey(Data->HasField(ANSI_TO_TCHAR("key")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("key"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("value"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>());
    }

    TSharedPtr<FJsonObject> FTimeseriesValue::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (KeyValue.IsSet())
        {
            JsonRootObject->SetStringField("key", KeyValue.GetValue());
        }
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("value", ValueValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FTimeseriesValue::TypeName = "TimeseriesValue";
}