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
#include "RepeatSetting.h"

namespace Gs2::Schedule::Model
{
    class GS2SCHEDULE_API FEventMaster final : public Gs2Object, public TSharedFromThis<FEventMaster>
    {
        TOptional<FString> EventIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ScheduleTypeValue;
        TOptional<int64> AbsoluteBeginValue;
        TOptional<int64> AbsoluteEndValue;
        TOptional<FString> RelativeTriggerNameValue;
        TSharedPtr<FRepeatSetting> RepeatSettingValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;
        TOptional<FString> RepeatTypeValue;
        TOptional<int32> RepeatBeginDayOfMonthValue;
        TOptional<int32> RepeatEndDayOfMonthValue;
        TOptional<FString> RepeatBeginDayOfWeekValue;
        TOptional<FString> RepeatEndDayOfWeekValue;
        TOptional<int32> RepeatBeginHourValue;
        TOptional<int32> RepeatEndHourValue;

    public:
        FEventMaster();
        FEventMaster(
            const FEventMaster& From
        );
        virtual ~FEventMaster() override = default;

        TSharedPtr<FEventMaster> WithEventId(const TOptional<FString> EventId);
        TSharedPtr<FEventMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FEventMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FEventMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEventMaster> WithScheduleType(const TOptional<FString> ScheduleType);
        TSharedPtr<FEventMaster> WithAbsoluteBegin(const TOptional<int64> AbsoluteBegin);
        TSharedPtr<FEventMaster> WithAbsoluteEnd(const TOptional<int64> AbsoluteEnd);
        TSharedPtr<FEventMaster> WithRelativeTriggerName(const TOptional<FString> RelativeTriggerName);
        TSharedPtr<FEventMaster> WithRepeatSetting(const TSharedPtr<FRepeatSetting> RepeatSetting);
        TSharedPtr<FEventMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEventMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FEventMaster> WithRevision(const TOptional<int64> Revision);
        TSharedPtr<FEventMaster> WithRepeatType(const TOptional<FString> RepeatType);
        TSharedPtr<FEventMaster> WithRepeatBeginDayOfMonth(const TOptional<int32> RepeatBeginDayOfMonth);
        TSharedPtr<FEventMaster> WithRepeatEndDayOfMonth(const TOptional<int32> RepeatEndDayOfMonth);
        TSharedPtr<FEventMaster> WithRepeatBeginDayOfWeek(const TOptional<FString> RepeatBeginDayOfWeek);
        TSharedPtr<FEventMaster> WithRepeatEndDayOfWeek(const TOptional<FString> RepeatEndDayOfWeek);
        TSharedPtr<FEventMaster> WithRepeatBeginHour(const TOptional<int32> RepeatBeginHour);
        TSharedPtr<FEventMaster> WithRepeatEndHour(const TOptional<int32> RepeatEndHour);

        TOptional<FString> GetEventId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetScheduleType() const;
        TOptional<int64> GetAbsoluteBegin() const;
        FString GetAbsoluteBeginString() const;
        TOptional<int64> GetAbsoluteEnd() const;
        FString GetAbsoluteEndString() const;
        TOptional<FString> GetRelativeTriggerName() const;
        TSharedPtr<FRepeatSetting> GetRepeatSetting() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;
        TOptional<FString> GetRepeatType() const;
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

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetEventNameFromGrn(const FString Grn);

        static TSharedPtr<FEventMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FEventMaster, ESPMode::ThreadSafe> FEventMasterPtr;
}