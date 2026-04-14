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

#include "Log/Model/FacetValueCount.h"

namespace Gs2::Log::Model
{
    FFacetValueCount::FFacetValueCount():
        ValueValue(TOptional<FString>()),
        CountValue(TOptional<int64>())
    {
    }

    FFacetValueCount::FFacetValueCount(
        const FFacetValueCount& From
    ):
        ValueValue(From.ValueValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FFacetValueCount> FFacetValueCount::WithValue(
        const TOptional<FString> Value
    )
    {
        this->ValueValue = Value;
        return SharedThis(this);
    }

    TSharedPtr<FFacetValueCount> FFacetValueCount::WithCount(
        const TOptional<int64> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FFacetValueCount::GetValue() const
    {
        return ValueValue;
    }
    TOptional<int64> FFacetValueCount::GetCount() const
    {
        return CountValue;
    }

    FString FFacetValueCount::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CountValue.GetValue());
    }

    TSharedPtr<FFacetValueCount> FFacetValueCount::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFacetValueCount>()
            ->WithValue(Data->HasField(ANSI_TO_TCHAR("value")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("value"), v))
                    {
                        return TOptional(v);
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

    TSharedPtr<FJsonObject> FFacetValueCount::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ValueValue.IsSet())
        {
            JsonRootObject->SetStringField("value", ValueValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetStringField("count", FString::Printf(TEXT("%lld"), CountValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FFacetValueCount::TypeName = "FacetValueCount";
}