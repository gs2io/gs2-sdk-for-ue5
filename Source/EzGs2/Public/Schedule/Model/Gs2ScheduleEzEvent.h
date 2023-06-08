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
#include "Schedule/Model/Event.h"

namespace Gs2::UE5::Schedule::Model
{
	class EZGS2_API FEzEvent final : public TSharedFromThis<FEzEvent>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScheduleTypeValue;
        TOptional<FString> RepeatTypeValue;
        TOptional<int64> AbsoluteBeginValue;
        TOptional<int64> AbsoluteEndValue;
        TOptional<int32> RepeatBeginDayOfMonthValue;
        TOptional<int32> RepeatEndDayOfMonthValue;
        TOptional<FString> RepeatBeginDayOfWeekValue;
        TOptional<FString> RepeatEndDayOfWeekValue;
        TOptional<int32> RepeatBeginHourValue;
        TOptional<int32> RepeatEndHourValue;
        TOptional<FString> RelativeTriggerNameValue;

	public:
        TSharedPtr<FEzEvent> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzEvent> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzEvent> WithScheduleType(const TOptional<FString> ScheduleType);
        TSharedPtr<FEzEvent> WithRepeatType(const TOptional<FString> RepeatType);
        TSharedPtr<FEzEvent> WithAbsoluteBegin(const TOptional<int64> AbsoluteBegin);
        TSharedPtr<FEzEvent> WithAbsoluteEnd(const TOptional<int64> AbsoluteEnd);
        TSharedPtr<FEzEvent> WithRepeatBeginDayOfMonth(const TOptional<int32> RepeatBeginDayOfMonth);
        TSharedPtr<FEzEvent> WithRepeatEndDayOfMonth(const TOptional<int32> RepeatEndDayOfMonth);
        TSharedPtr<FEzEvent> WithRepeatBeginDayOfWeek(const TOptional<FString> RepeatBeginDayOfWeek);
        TSharedPtr<FEzEvent> WithRepeatEndDayOfWeek(const TOptional<FString> RepeatEndDayOfWeek);
        TSharedPtr<FEzEvent> WithRepeatBeginHour(const TOptional<int32> RepeatBeginHour);
        TSharedPtr<FEzEvent> WithRepeatEndHour(const TOptional<int32> RepeatEndHour);
        TSharedPtr<FEzEvent> WithRelativeTriggerName(const TOptional<FString> RelativeTriggerName);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetScheduleType() const;

        TOptional<FString> GetRepeatType() const;

        TOptional<int64> GetAbsoluteBegin() const;
        FString GetAbsoluteBeginString() const;

        TOptional<int64> GetAbsoluteEnd() const;
        FString GetAbsoluteEndString() const;

        TOptional<int32> GetRepeatBeginDayOfMonth() const;
        FString GetRepeatBeginDayOfMonthString() const;

        TOptional<int32> GetRepeatEndDayOfMonth() const;
        FString GetRepeatEndDayOfMonthString() const;

        TOptional<FString> GetRepeatBeginDayOfWeek() const;

        TOptional<FString> GetRepeatEndDayOfWeek() const;

        TOptional<int32> GetRepeatBeginHour() const;
        FString GetRepeatBeginHourString() const;

        TOptional<int32> GetRepeatEndHour() const;
        FString GetRepeatEndHourString() const;

        TOptional<FString> GetRelativeTriggerName() const;

        Gs2::Schedule::Model::FEventPtr ToModel() const;
        static TSharedPtr<FEzEvent> FromModel(Gs2::Schedule::Model::FEventPtr Model);
    };
    typedef TSharedPtr<FEzEvent> FEzEventPtr;
}