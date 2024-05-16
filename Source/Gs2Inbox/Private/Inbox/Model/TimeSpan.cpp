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

#include "Inbox/Model/TimeSpan.h"

namespace Gs2::Inbox::Model
{
    FTimeSpan::FTimeSpan():
        DaysValue(TOptional<int32>()),
        HoursValue(TOptional<int32>()),
        MinutesValue(TOptional<int32>())
    {
    }

    FTimeSpan::FTimeSpan(
        const FTimeSpan& From
    ):
        DaysValue(From.DaysValue),
        HoursValue(From.HoursValue),
        MinutesValue(From.MinutesValue)
    {
    }

    TSharedPtr<FTimeSpan> FTimeSpan::WithDays(
        const TOptional<int32> Days
    )
    {
        this->DaysValue = Days;
        return SharedThis(this);
    }

    TSharedPtr<FTimeSpan> FTimeSpan::WithHours(
        const TOptional<int32> Hours
    )
    {
        this->HoursValue = Hours;
        return SharedThis(this);
    }

    TSharedPtr<FTimeSpan> FTimeSpan::WithMinutes(
        const TOptional<int32> Minutes
    )
    {
        this->MinutesValue = Minutes;
        return SharedThis(this);
    }
    TOptional<int32> FTimeSpan::GetDays() const
    {
        return DaysValue;
    }

    FString FTimeSpan::GetDaysString() const
    {
        if (!DaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DaysValue.GetValue());
    }
    TOptional<int32> FTimeSpan::GetHours() const
    {
        return HoursValue;
    }

    FString FTimeSpan::GetHoursString() const
    {
        if (!HoursValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), HoursValue.GetValue());
    }
    TOptional<int32> FTimeSpan::GetMinutes() const
    {
        return MinutesValue;
    }

    FString FTimeSpan::GetMinutesString() const
    {
        if (!MinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinutesValue.GetValue());
    }

    TSharedPtr<FTimeSpan> FTimeSpan::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FTimeSpan>()
            ->WithDays(Data->HasField(ANSI_TO_TCHAR("days")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("days"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithHours(Data->HasField(ANSI_TO_TCHAR("hours")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("hours"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMinutes(Data->HasField(ANSI_TO_TCHAR("minutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("minutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FTimeSpan::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("days", DaysValue.GetValue());
        }
        if (HoursValue.IsSet())
        {
            JsonRootObject->SetNumberField("hours", HoursValue.GetValue());
        }
        if (MinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("minutes", MinutesValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FTimeSpan::TypeName = "TimeSpan";
}