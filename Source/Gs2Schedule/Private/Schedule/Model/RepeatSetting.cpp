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

#include "Schedule/Model/RepeatSetting.h"

namespace Gs2::Schedule::Model
{
    FRepeatSetting::FRepeatSetting():
        RepeatTypeValue(TOptional<FString>()),
        BeginDayOfMonthValue(TOptional<int32>()),
        EndDayOfMonthValue(TOptional<int32>()),
        BeginDayOfWeekValue(TOptional<FString>()),
        EndDayOfWeekValue(TOptional<FString>()),
        BeginHourValue(TOptional<int32>()),
        EndHourValue(TOptional<int32>())
    {
    }

    FRepeatSetting::FRepeatSetting(
        const FRepeatSetting& From
    ):
        RepeatTypeValue(From.RepeatTypeValue),
        BeginDayOfMonthValue(From.BeginDayOfMonthValue),
        EndDayOfMonthValue(From.EndDayOfMonthValue),
        BeginDayOfWeekValue(From.BeginDayOfWeekValue),
        EndDayOfWeekValue(From.EndDayOfWeekValue),
        BeginHourValue(From.BeginHourValue),
        EndHourValue(From.EndHourValue)
    {
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::WithRepeatType(
        const TOptional<FString> RepeatType
    )
    {
        this->RepeatTypeValue = RepeatType;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::WithBeginDayOfMonth(
        const TOptional<int32> BeginDayOfMonth
    )
    {
        this->BeginDayOfMonthValue = BeginDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::WithEndDayOfMonth(
        const TOptional<int32> EndDayOfMonth
    )
    {
        this->EndDayOfMonthValue = EndDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::WithBeginDayOfWeek(
        const TOptional<FString> BeginDayOfWeek
    )
    {
        this->BeginDayOfWeekValue = BeginDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::WithEndDayOfWeek(
        const TOptional<FString> EndDayOfWeek
    )
    {
        this->EndDayOfWeekValue = EndDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::WithBeginHour(
        const TOptional<int32> BeginHour
    )
    {
        this->BeginHourValue = BeginHour;
        return SharedThis(this);
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::WithEndHour(
        const TOptional<int32> EndHour
    )
    {
        this->EndHourValue = EndHour;
        return SharedThis(this);
    }
    TOptional<FString> FRepeatSetting::GetRepeatType() const
    {
        return RepeatTypeValue;
    }
    TOptional<int32> FRepeatSetting::GetBeginDayOfMonth() const
    {
        return BeginDayOfMonthValue;
    }

    FString FRepeatSetting::GetBeginDayOfMonthString() const
    {
        if (!BeginDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), BeginDayOfMonthValue.GetValue());
    }
    TOptional<int32> FRepeatSetting::GetEndDayOfMonth() const
    {
        return EndDayOfMonthValue;
    }

    FString FRepeatSetting::GetEndDayOfMonthString() const
    {
        if (!EndDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), EndDayOfMonthValue.GetValue());
    }
    TOptional<FString> FRepeatSetting::GetBeginDayOfWeek() const
    {
        return BeginDayOfWeekValue;
    }
    TOptional<FString> FRepeatSetting::GetEndDayOfWeek() const
    {
        return EndDayOfWeekValue;
    }
    TOptional<int32> FRepeatSetting::GetBeginHour() const
    {
        return BeginHourValue;
    }

    FString FRepeatSetting::GetBeginHourString() const
    {
        if (!BeginHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), BeginHourValue.GetValue());
    }
    TOptional<int32> FRepeatSetting::GetEndHour() const
    {
        return EndHourValue;
    }

    FString FRepeatSetting::GetEndHourString() const
    {
        if (!EndHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), EndHourValue.GetValue());
    }

    TSharedPtr<FRepeatSetting> FRepeatSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRepeatSetting>()
            ->WithRepeatType(Data->HasField(ANSI_TO_TCHAR("repeatType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("repeatType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBeginDayOfMonth(Data->HasField(ANSI_TO_TCHAR("beginDayOfMonth")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("beginDayOfMonth"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithEndDayOfMonth(Data->HasField(ANSI_TO_TCHAR("endDayOfMonth")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("endDayOfMonth"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithBeginDayOfWeek(Data->HasField(ANSI_TO_TCHAR("beginDayOfWeek")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("beginDayOfWeek"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithEndDayOfWeek(Data->HasField(ANSI_TO_TCHAR("endDayOfWeek")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("endDayOfWeek"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBeginHour(Data->HasField(ANSI_TO_TCHAR("beginHour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("beginHour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithEndHour(Data->HasField(ANSI_TO_TCHAR("endHour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("endHour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FRepeatSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RepeatTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("repeatType", RepeatTypeValue.GetValue());
        }
        if (BeginDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("beginDayOfMonth", BeginDayOfMonthValue.GetValue());
        }
        if (EndDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("endDayOfMonth", EndDayOfMonthValue.GetValue());
        }
        if (BeginDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("beginDayOfWeek", BeginDayOfWeekValue.GetValue());
        }
        if (EndDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("endDayOfWeek", EndDayOfWeekValue.GetValue());
        }
        if (BeginHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("beginHour", BeginHourValue.GetValue());
        }
        if (EndHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("endHour", EndHourValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FRepeatSetting::TypeName = "RepeatSetting";
}