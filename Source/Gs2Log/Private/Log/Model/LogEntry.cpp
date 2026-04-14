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

#include "Log/Model/LogEntry.h"

namespace Gs2::Log::Model
{
    FLogEntry::FLogEntry():
        TimestampValue(TOptional<int64>()),
        StatusValue(TOptional<FString>()),
        DurationValue(TOptional<int64>()),
        LineValue(TOptional<FString>()),
        LabelsValue(nullptr)
    {
    }

    FLogEntry::FLogEntry(
        const FLogEntry& From
    ):
        TimestampValue(From.TimestampValue),
        StatusValue(From.StatusValue),
        DurationValue(From.DurationValue),
        LineValue(From.LineValue),
        LabelsValue(From.LabelsValue)
    {
    }

    TSharedPtr<FLogEntry> FLogEntry::WithTimestamp(
        const TOptional<int64> Timestamp
    )
    {
        this->TimestampValue = Timestamp;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithDuration(
        const TOptional<int64> Duration
    )
    {
        this->DurationValue = Duration;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithLine(
        const TOptional<FString> Line
    )
    {
        this->LineValue = Line;
        return SharedThis(this);
    }

    TSharedPtr<FLogEntry> FLogEntry::WithLabels(
        const TSharedPtr<TArray<TSharedPtr<Model::FLabel>>> Labels
    )
    {
        this->LabelsValue = Labels;
        return SharedThis(this);
    }
    TOptional<int64> FLogEntry::GetTimestamp() const
    {
        return TimestampValue;
    }

    FString FLogEntry::GetTimestampString() const
    {
        if (!TimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TimestampValue.GetValue());
    }
    TOptional<FString> FLogEntry::GetStatus() const
    {
        return StatusValue;
    }
    TOptional<int64> FLogEntry::GetDuration() const
    {
        return DurationValue;
    }

    FString FLogEntry::GetDurationString() const
    {
        if (!DurationValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DurationValue.GetValue());
    }
    TOptional<FString> FLogEntry::GetLine() const
    {
        return LineValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FLabel>>> FLogEntry::GetLabels() const
    {
        return LabelsValue;
    }

    TSharedPtr<FLogEntry> FLogEntry::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLogEntry>()
            ->WithTimestamp(Data->HasField(ANSI_TO_TCHAR("timestamp")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("timestamp"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("status"), v))
                    {
                        return TOptional(v);
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
            ->WithLine(Data->HasField(ANSI_TO_TCHAR("line")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("line"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLabels(Data->HasField(ANSI_TO_TCHAR("labels")) ? [Data]() -> TSharedPtr<TArray<Model::FLabelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FLabelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("labels")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("labels")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("labels")))
                        {
                            v->Add(Model::FLabel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FLabelPtr>>());
    }

    TSharedPtr<FJsonObject> FLogEntry::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("timestamp", FString::Printf(TEXT("%lld"), TimestampValue.GetValue()));
        }
        if (StatusValue.IsSet())
        {
            JsonRootObject->SetStringField("status", StatusValue.GetValue());
        }
        if (DurationValue.IsSet())
        {
            JsonRootObject->SetStringField("duration", FString::Printf(TEXT("%lld"), DurationValue.GetValue()));
        }
        if (LineValue.IsSet())
        {
            JsonRootObject->SetStringField("line", LineValue.GetValue());
        }
        if (LabelsValue != nullptr && LabelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *LabelsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("labels", v);
        }
        return JsonRootObject;
    }

    FString FLogEntry::TypeName = "LogEntry";
}