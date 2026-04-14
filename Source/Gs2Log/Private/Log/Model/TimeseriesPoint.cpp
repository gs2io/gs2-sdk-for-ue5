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

#include "Log/Model/TimeseriesPoint.h"

namespace Gs2::Log::Model
{
    FTimeseriesPoint::FTimeseriesPoint():
        TimestampValue(TOptional<int64>()),
        ValuesValue(nullptr)
    {
    }

    FTimeseriesPoint::FTimeseriesPoint(
        const FTimeseriesPoint& From
    ):
        TimestampValue(From.TimestampValue),
        ValuesValue(From.ValuesValue)
    {
    }

    TSharedPtr<FTimeseriesPoint> FTimeseriesPoint::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FTimeseriesPoint> FTimeseriesPoint::WithValues(
        const TSharedPtr<TArray<TSharedPtr<Model::FTimeseriesValue>>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }
    TOptional<int64> FTimeseriesPoint::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FTimeseriesPoint::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FTimeseriesValue>>> FTimeseriesPoint::GetValues() const
    {
        return ValuesValue;
    }

    TSharedPtr<FTimeseriesPoint> FTimeseriesPoint::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTimeseriesPoint>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithValues(Data->HasField(ANSI_TO_TCHAR("values")) ? [Data]() -> TSharedPtr<TArray<Model::FTimeseriesValuePtr>>
                {
                    auto v = MakeShared<TArray<Model::FTimeseriesValuePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("values")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("values")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("values")))
                        {
                            v->Add(Model::FTimeseriesValue::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FTimeseriesValuePtr>>());
    }

    TSharedPtr<FJsonObject> FTimeseriesPoint::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (ValuesValue != nullptr && ValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ValuesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("values", v);
        }
        return JsonRootObject;
    }

    FString FTimeseriesPoint::TypeName = "TimeseriesPoint";
}