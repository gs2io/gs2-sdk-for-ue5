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

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"

namespace Gs2::Schedule::Model
{
    class GS2SCHEDULE_API FRepeatSetting final : public FGs2Object, public TSharedFromThis<FRepeatSetting>
    {
        TOptional<FString> RepeatTypeValue;
        TOptional<int32> BeginDayOfMonthValue;
        TOptional<int32> EndDayOfMonthValue;
        TOptional<FString> BeginDayOfWeekValue;
        TOptional<FString> EndDayOfWeekValue;
        TOptional<int32> BeginHourValue;
        TOptional<int32> EndHourValue;
        TOptional<int64> AnchorTimestampValue;
        TOptional<int32> ActiveDaysValue;
        TOptional<int32> InactiveDaysValue;

    public:
        FRepeatSetting();
        FRepeatSetting(
            const FRepeatSetting& From
        );
        virtual ~FRepeatSetting() override = default;

        TSharedPtr<FRepeatSetting> WithRepeatType(const TOptional<FString> RepeatType);
        TSharedPtr<FRepeatSetting> WithBeginDayOfMonth(const TOptional<int32> BeginDayOfMonth);
        TSharedPtr<FRepeatSetting> WithEndDayOfMonth(const TOptional<int32> EndDayOfMonth);
        TSharedPtr<FRepeatSetting> WithBeginDayOfWeek(const TOptional<FString> BeginDayOfWeek);
        TSharedPtr<FRepeatSetting> WithEndDayOfWeek(const TOptional<FString> EndDayOfWeek);
        TSharedPtr<FRepeatSetting> WithBeginHour(const TOptional<int32> BeginHour);
        TSharedPtr<FRepeatSetting> WithEndHour(const TOptional<int32> EndHour);
        TSharedPtr<FRepeatSetting> WithAnchorTimestamp(const TOptional<int64> AnchorTimestamp);
        TSharedPtr<FRepeatSetting> WithActiveDays(const TOptional<int32> ActiveDays);
        TSharedPtr<FRepeatSetting> WithInactiveDays(const TOptional<int32> InactiveDays);

        TOptional<FString> GetRepeatType() const;
        TOptional<int32> GetBeginDayOfMonth() const;
        FString GetBeginDayOfMonthString() const;
        TOptional<int32> GetEndDayOfMonth() const;
        FString GetEndDayOfMonthString() const;
        TOptional<FString> GetBeginDayOfWeek() const;
        TOptional<FString> GetEndDayOfWeek() const;
        TOptional<int32> GetBeginHour() const;
        FString GetBeginHourString() const;
        TOptional<int32> GetEndHour() const;
        FString GetEndHourString() const;
        TOptional<int64> GetAnchorTimestamp() const;
        FString GetAnchorTimestampString() const;
        TOptional<int32> GetActiveDays() const;
        FString GetActiveDaysString() const;
        TOptional<int32> GetInactiveDays() const;
        FString GetInactiveDaysString() const;


        static TSharedPtr<FRepeatSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRepeatSetting, ESPMode::ThreadSafe> FRepeatSettingPtr;
}