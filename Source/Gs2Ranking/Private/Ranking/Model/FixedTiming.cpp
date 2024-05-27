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

#include "Ranking/Model/FixedTiming.h"

namespace Gs2::Ranking::Model
{
    FFixedTiming::FFixedTiming():
        HourValue(TOptional<int32>()),
        MinuteValue(TOptional<int32>())
    {
    }

    FFixedTiming::FFixedTiming(
        const FFixedTiming& From
    ):
        HourValue(From.HourValue),
        MinuteValue(From.MinuteValue)
    {
    }

    TSharedPtr<FFixedTiming> FFixedTiming::WithHour(
        const TOptional<int32> Hour
    )
    {
        this->HourValue = Hour;
        return SharedThis(this);
    }

    TSharedPtr<FFixedTiming> FFixedTiming::WithMinute(
        const TOptional<int32> Minute
    )
    {
        this->MinuteValue = Minute;
        return SharedThis(this);
    }
    TOptional<int32> FFixedTiming::GetHour() const
    {
        return HourValue;
    }

    FString FFixedTiming::GetHourString() const
    {
        if (!HourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), HourValue.GetValue());
    }
    TOptional<int32> FFixedTiming::GetMinute() const
    {
        return MinuteValue;
    }

    FString FFixedTiming::GetMinuteString() const
    {
        if (!MinuteValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinuteValue.GetValue());
    }

    TSharedPtr<FFixedTiming> FFixedTiming::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFixedTiming>()
            ->WithHour(Data->HasField(ANSI_TO_TCHAR("hour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("hour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMinute(Data->HasField(ANSI_TO_TCHAR("minute")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("minute"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FFixedTiming::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (HourValue.IsSet())
        {
            JsonRootObject->SetNumberField("hour", HourValue.GetValue());
        }
        if (MinuteValue.IsSet())
        {
            JsonRootObject->SetNumberField("minute", MinuteValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FFixedTiming::TypeName = "FixedTiming";
}