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
    class GS2SCHEDULE_API FEvent final : public Gs2Object, public TSharedFromThis<FEvent>
    {
        TOptional<FString> EventIdValue;
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
        FEvent();
        FEvent(
            const FEvent& From
        );
        virtual ~FEvent() override = default;

        TSharedPtr<FEvent> WithEventId(const TOptional<FString> EventId);
        TSharedPtr<FEvent> WithName(const TOptional<FString> Name);
        TSharedPtr<FEvent> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEvent> WithScheduleType(const TOptional<FString> ScheduleType);
        TSharedPtr<FEvent> WithRepeatType(const TOptional<FString> RepeatType);
        TSharedPtr<FEvent> WithAbsoluteBegin(const TOptional<int64> AbsoluteBegin);
        TSharedPtr<FEvent> WithAbsoluteEnd(const TOptional<int64> AbsoluteEnd);
        TSharedPtr<FEvent> WithRepeatBeginDayOfMonth(const TOptional<int32> RepeatBeginDayOfMonth);
        TSharedPtr<FEvent> WithRepeatEndDayOfMonth(const TOptional<int32> RepeatEndDayOfMonth);
        TSharedPtr<FEvent> WithRepeatBeginDayOfWeek(const TOptional<FString> RepeatBeginDayOfWeek);
        TSharedPtr<FEvent> WithRepeatEndDayOfWeek(const TOptional<FString> RepeatEndDayOfWeek);
        TSharedPtr<FEvent> WithRepeatBeginHour(const TOptional<int32> RepeatBeginHour);
        TSharedPtr<FEvent> WithRepeatEndHour(const TOptional<int32> RepeatEndHour);
        TSharedPtr<FEvent> WithRelativeTriggerName(const TOptional<FString> RelativeTriggerName);

        TOptional<FString> GetEventId() const;
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

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetEventNameFromGrn(const FString Grn);

        static TSharedPtr<FEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEvent, ESPMode::ThreadSafe> FEventPtr;
}