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

#include "Log/Model/NumericRange.h"

namespace Gs2::Log::Model
{
    FNumericRange::FNumericRange():
        MinValue(TOptional<double>()),
        MaxValue(TOptional<double>())
    {
    }

    FNumericRange::FNumericRange(
        const FNumericRange& From
    ):
        MinValue(From.MinValue),
        MaxValue(From.MaxValue)
    {
    }

    TSharedPtr<FNumericRange> FNumericRange::WithMin(
        const TOptional<double> Min
    )
    {
        this->MinValue = Min;
        return SharedThis(this);
    }

    TSharedPtr<FNumericRange> FNumericRange::WithMax(
        const TOptional<double> Max
    )
    {
        this->MaxValue = Max;
        return SharedThis(this);
    }
    TOptional<double> FNumericRange::GetMin() const
    {
        return MinValue;
    }

    FString FNumericRange::GetMinString() const
    {
        if (!MinValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), MinValue.GetValue());
    }
    TOptional<double> FNumericRange::GetMax() const
    {
        return MaxValue;
    }

    FString FNumericRange::GetMaxString() const
    {
        if (!MaxValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), MaxValue.GetValue());
    }

    TSharedPtr<FNumericRange> FNumericRange::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNumericRange>()
            ->WithMin(Data->HasField(ANSI_TO_TCHAR("min")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("min"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithMax(Data->HasField(ANSI_TO_TCHAR("max")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("max"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>());
    }

    TSharedPtr<FJsonObject> FNumericRange::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MinValue.IsSet())
        {
            JsonRootObject->SetNumberField("min", MinValue.GetValue());
        }
        if (MaxValue.IsSet())
        {
            JsonRootObject->SetNumberField("max", MaxValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FNumericRange::TypeName = "NumericRange";
}