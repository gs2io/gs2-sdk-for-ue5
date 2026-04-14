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

#include "Log/Model/Trace.h"

namespace Gs2::Log::Model
{
    FTrace::FTrace():
        TraceIdValue(TOptional<FString>()),
        SpansValue(nullptr),
        TruncatedValue(TOptional<bool>())
    {
    }

    FTrace::FTrace(
        const FTrace& From
    ):
        TraceIdValue(From.TraceIdValue),
        SpansValue(From.SpansValue),
        TruncatedValue(From.TruncatedValue)
    {
    }

    TSharedPtr<FTrace> FTrace::WithTraceId(
        const TOptional<FString> TraceId
    )
    {
        this->TraceIdValue = TraceId;
        return SharedThis(this);
    }

    TSharedPtr<FTrace> FTrace::WithSpans(
        const TSharedPtr<TArray<TSharedPtr<Model::FLogEntry>>> Spans
    )
    {
        this->SpansValue = Spans;
        return SharedThis(this);
    }

    TSharedPtr<FTrace> FTrace::WithTruncated(
        const TOptional<bool> Truncated
    )
    {
        this->TruncatedValue = Truncated;
        return SharedThis(this);
    }
    TOptional<FString> FTrace::GetTraceId() const
    {
        return TraceIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FLogEntry>>> FTrace::GetSpans() const
    {
        return SpansValue;
    }
    TOptional<bool> FTrace::GetTruncated() const
    {
        return TruncatedValue;
    }

    FString FTrace::GetTruncatedString() const
    {
        if (!TruncatedValue.IsSet())
        {
            return FString("null");
        }
        return FString(TruncatedValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FTrace> FTrace::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTrace>()
            ->WithTraceId(Data->HasField(ANSI_TO_TCHAR("traceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("traceId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSpans(Data->HasField(ANSI_TO_TCHAR("spans")) ? [Data]() -> TSharedPtr<TArray<Model::FLogEntryPtr>>
                {
                    auto v = MakeShared<TArray<Model::FLogEntryPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("spans")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("spans")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("spans")))
                        {
                            v->Add(Model::FLogEntry::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FLogEntryPtr>>())
            ->WithTruncated(Data->HasField(ANSI_TO_TCHAR("truncated")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("truncated"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FTrace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TraceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("traceId", TraceIdValue.GetValue());
        }
        if (SpansValue != nullptr && SpansValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SpansValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("spans", v);
        }
        if (TruncatedValue.IsSet())
        {
            JsonRootObject->SetBoolField("truncated", TruncatedValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FTrace::TypeName = "Trace";
}