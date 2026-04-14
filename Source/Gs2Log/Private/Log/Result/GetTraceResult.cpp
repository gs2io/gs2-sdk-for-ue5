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

#include "Log/Result/GetTraceResult.h"

namespace Gs2::Log::Result
{
    FGetTraceResult::FGetTraceResult():
        TraceValue(nullptr),
        ParallelsValue(nullptr),
        ParallelTruncatedValue(TOptional<bool>())
    {
    }

    FGetTraceResult::FGetTraceResult(
        const FGetTraceResult& From
    ):
        TraceValue(From.TraceValue),
        ParallelsValue(From.ParallelsValue),
        ParallelTruncatedValue(From.ParallelTruncatedValue)
    {
    }

    TSharedPtr<FGetTraceResult> FGetTraceResult::WithTrace(
        const TSharedPtr<Model::FTrace> Trace
    )
    {
        this->TraceValue = Trace;
        return SharedThis(this);
    }

    TSharedPtr<FGetTraceResult> FGetTraceResult::WithParallels(
        const TSharedPtr<TArray<TSharedPtr<Model::FTrace>>> Parallels
    )
    {
        this->ParallelsValue = Parallels;
        return SharedThis(this);
    }

    TSharedPtr<FGetTraceResult> FGetTraceResult::WithParallelTruncated(
        const TOptional<bool> ParallelTruncated
    )
    {
        this->ParallelTruncatedValue = ParallelTruncated;
        return SharedThis(this);
    }

    TSharedPtr<Model::FTrace> FGetTraceResult::GetTrace() const
    {
        if (!TraceValue.IsValid())
        {
            return nullptr;
        }
        return TraceValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FTrace>>> FGetTraceResult::GetParallels() const
    {
        if (!ParallelsValue.IsValid())
        {
            return nullptr;
        }
        return ParallelsValue;
    }

    TOptional<bool> FGetTraceResult::GetParallelTruncated() const
    {
        return ParallelTruncatedValue;
    }

    FString FGetTraceResult::GetParallelTruncatedString() const
    {
        if (!ParallelTruncatedValue.IsSet())
        {
            return FString("null");
        }
        return FString(ParallelTruncatedValue.GetValue() ? "true" : "false");
    }

    TSharedPtr<FGetTraceResult> FGetTraceResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetTraceResult>()
            ->WithTrace(Data->HasField(ANSI_TO_TCHAR("trace")) ? [Data]() -> Model::FTracePtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("trace")))
                    {
                        return nullptr;
                    }
                    return Model::FTrace::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("trace")));
                 }() : nullptr)
            ->WithParallels(Data->HasField(ANSI_TO_TCHAR("parallels")) ? [Data]() -> TSharedPtr<TArray<Model::FTracePtr>>
                 {
                    auto v = MakeShared<TArray<Model::FTracePtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("parallels")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("parallels")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("parallels")))
                        {
                            v->Add(Model::FTrace::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FTracePtr>>())
            ->WithParallelTruncated(Data->HasField(ANSI_TO_TCHAR("parallelTruncated")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("parallelTruncated"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>());
    }

    TSharedPtr<FJsonObject> FGetTraceResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TraceValue != nullptr && TraceValue.IsValid())
        {
            JsonRootObject->SetObjectField("trace", TraceValue->ToJson());
        }
        if (ParallelsValue != nullptr && ParallelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ParallelsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("parallels", v);
        }
        if (ParallelTruncatedValue.IsSet())
        {
            JsonRootObject->SetBoolField("parallelTruncated", ParallelTruncatedValue.GetValue());
        }
        return JsonRootObject;
    }
}