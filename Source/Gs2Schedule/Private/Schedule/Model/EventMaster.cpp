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

#include "Schedule/Model/EventMaster.h"

namespace Gs2::Schedule::Model
{
    FEventMaster::FEventMaster():
        EventIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ScheduleTypeValue(TOptional<FString>()),
        RepeatTypeValue(TOptional<FString>()),
        AbsoluteBeginValue(TOptional<int64>()),
        AbsoluteEndValue(TOptional<int64>()),
        RepeatBeginDayOfMonthValue(TOptional<int32>()),
        RepeatEndDayOfMonthValue(TOptional<int32>()),
        RepeatBeginDayOfWeekValue(TOptional<FString>()),
        RepeatEndDayOfWeekValue(TOptional<FString>()),
        RepeatBeginHourValue(TOptional<int32>()),
        RepeatEndHourValue(TOptional<int32>()),
        RelativeTriggerNameValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>())
    {
    }

    FEventMaster::FEventMaster(
        const FEventMaster& From
    ):
        EventIdValue(From.EventIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ScheduleTypeValue(From.ScheduleTypeValue),
        RepeatTypeValue(From.RepeatTypeValue),
        AbsoluteBeginValue(From.AbsoluteBeginValue),
        AbsoluteEndValue(From.AbsoluteEndValue),
        RepeatBeginDayOfMonthValue(From.RepeatBeginDayOfMonthValue),
        RepeatEndDayOfMonthValue(From.RepeatEndDayOfMonthValue),
        RepeatBeginDayOfWeekValue(From.RepeatBeginDayOfWeekValue),
        RepeatEndDayOfWeekValue(From.RepeatEndDayOfWeekValue),
        RepeatBeginHourValue(From.RepeatBeginHourValue),
        RepeatEndHourValue(From.RepeatEndHourValue),
        RelativeTriggerNameValue(From.RelativeTriggerNameValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue)
    {
    }

    TSharedPtr<FEventMaster> FEventMaster::WithEventId(
        const TOptional<FString> EventId
    )
    {
        this->EventIdValue = EventId;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithScheduleType(
        const TOptional<FString> ScheduleType
    )
    {
        this->ScheduleTypeValue = ScheduleType;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatType(
        const TOptional<FString> RepeatType
    )
    {
        this->RepeatTypeValue = RepeatType;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithAbsoluteBegin(
        const TOptional<int64> AbsoluteBegin
    )
    {
        this->AbsoluteBeginValue = AbsoluteBegin;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithAbsoluteEnd(
        const TOptional<int64> AbsoluteEnd
    )
    {
        this->AbsoluteEndValue = AbsoluteEnd;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatBeginDayOfMonth(
        const TOptional<int32> RepeatBeginDayOfMonth
    )
    {
        this->RepeatBeginDayOfMonthValue = RepeatBeginDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatEndDayOfMonth(
        const TOptional<int32> RepeatEndDayOfMonth
    )
    {
        this->RepeatEndDayOfMonthValue = RepeatEndDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatBeginDayOfWeek(
        const TOptional<FString> RepeatBeginDayOfWeek
    )
    {
        this->RepeatBeginDayOfWeekValue = RepeatBeginDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatEndDayOfWeek(
        const TOptional<FString> RepeatEndDayOfWeek
    )
    {
        this->RepeatEndDayOfWeekValue = RepeatEndDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatBeginHour(
        const TOptional<int32> RepeatBeginHour
    )
    {
        this->RepeatBeginHourValue = RepeatBeginHour;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatEndHour(
        const TOptional<int32> RepeatEndHour
    )
    {
        this->RepeatEndHourValue = RepeatEndHour;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRelativeTriggerName(
        const TOptional<FString> RelativeTriggerName
    )
    {
        this->RelativeTriggerNameValue = RelativeTriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEventMaster::GetEventId() const
    {
        return EventIdValue;
    }
    TOptional<FString> FEventMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEventMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FEventMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEventMaster::GetScheduleType() const
    {
        return ScheduleTypeValue;
    }
    TOptional<FString> FEventMaster::GetRepeatType() const
    {
        return RepeatTypeValue;
    }
    TOptional<int64> FEventMaster::GetAbsoluteBegin() const
    {
        return AbsoluteBeginValue;
    }

    FString FEventMaster::GetAbsoluteBeginString() const
    {
        if (!AbsoluteBeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteBeginValue.GetValue());
    }
    TOptional<int64> FEventMaster::GetAbsoluteEnd() const
    {
        return AbsoluteEndValue;
    }

    FString FEventMaster::GetAbsoluteEndString() const
    {
        if (!AbsoluteEndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteEndValue.GetValue());
    }
    TOptional<int32> FEventMaster::GetRepeatBeginDayOfMonth() const
    {
        return RepeatBeginDayOfMonthValue;
    }

    FString FEventMaster::GetRepeatBeginDayOfMonthString() const
    {
        if (!RepeatBeginDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatBeginDayOfMonthValue.GetValue());
    }
    TOptional<int32> FEventMaster::GetRepeatEndDayOfMonth() const
    {
        return RepeatEndDayOfMonthValue;
    }

    FString FEventMaster::GetRepeatEndDayOfMonthString() const
    {
        if (!RepeatEndDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatEndDayOfMonthValue.GetValue());
    }
    TOptional<FString> FEventMaster::GetRepeatBeginDayOfWeek() const
    {
        return RepeatBeginDayOfWeekValue;
    }
    TOptional<FString> FEventMaster::GetRepeatEndDayOfWeek() const
    {
        return RepeatEndDayOfWeekValue;
    }
    TOptional<int32> FEventMaster::GetRepeatBeginHour() const
    {
        return RepeatBeginHourValue;
    }

    FString FEventMaster::GetRepeatBeginHourString() const
    {
        if (!RepeatBeginHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatBeginHourValue.GetValue());
    }
    TOptional<int32> FEventMaster::GetRepeatEndHour() const
    {
        return RepeatEndHourValue;
    }

    FString FEventMaster::GetRepeatEndHourString() const
    {
        if (!RepeatEndHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatEndHourValue.GetValue());
    }
    TOptional<FString> FEventMaster::GetRelativeTriggerName() const
    {
        return RelativeTriggerNameValue;
    }
    TOptional<int64> FEventMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEventMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FEventMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEventMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    TOptional<FString> FEventMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):schedule:(?<namespaceName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEventMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):schedule:(?<namespaceName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEventMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):schedule:(?<namespaceName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FEventMaster::GetEventNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):schedule:(?<namespaceName>.+):event:(?<eventName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FEventMaster> FEventMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FEventMaster>()
            ->WithEventId(Data->HasField("eventId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("eventId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScheduleType(Data->HasField("scheduleType") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scheduleType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepeatType(Data->HasField("repeatType") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("repeatType", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAbsoluteBegin(Data->HasField("absoluteBegin") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("absoluteBegin", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithAbsoluteEnd(Data->HasField("absoluteEnd") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("absoluteEnd", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRepeatBeginDayOfMonth(Data->HasField("repeatBeginDayOfMonth") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("repeatBeginDayOfMonth", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRepeatEndDayOfMonth(Data->HasField("repeatEndDayOfMonth") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("repeatEndDayOfMonth", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRepeatBeginDayOfWeek(Data->HasField("repeatBeginDayOfWeek") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("repeatBeginDayOfWeek", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepeatEndDayOfWeek(Data->HasField("repeatEndDayOfWeek") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("repeatEndDayOfWeek", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepeatBeginHour(Data->HasField("repeatBeginHour") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("repeatBeginHour", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRepeatEndHour(Data->HasField("repeatEndHour") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("repeatEndHour", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRelativeTriggerName(Data->HasField("relativeTriggerName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("relativeTriggerName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField("createdAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("createdAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField("updatedAt") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("updatedAt", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FEventMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (EventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("eventId", EventIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ScheduleTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("scheduleType", ScheduleTypeValue.GetValue());
        }
        if (RepeatTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("repeatType", RepeatTypeValue.GetValue());
        }
        if (AbsoluteBeginValue.IsSet())
        {
            JsonRootObject->SetStringField("absoluteBegin", FString::Printf(TEXT("%lld"), AbsoluteBeginValue.GetValue()));
        }
        if (AbsoluteEndValue.IsSet())
        {
            JsonRootObject->SetStringField("absoluteEnd", FString::Printf(TEXT("%lld"), AbsoluteEndValue.GetValue()));
        }
        if (RepeatBeginDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("repeatBeginDayOfMonth", RepeatBeginDayOfMonthValue.GetValue());
        }
        if (RepeatEndDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("repeatEndDayOfMonth", RepeatEndDayOfMonthValue.GetValue());
        }
        if (RepeatBeginDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("repeatBeginDayOfWeek", RepeatBeginDayOfWeekValue.GetValue());
        }
        if (RepeatEndDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("repeatEndDayOfWeek", RepeatEndDayOfWeekValue.GetValue());
        }
        if (RepeatBeginHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("repeatBeginHour", RepeatBeginHourValue.GetValue());
        }
        if (RepeatEndHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("repeatEndHour", RepeatEndHourValue.GetValue());
        }
        if (RelativeTriggerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("relativeTriggerName", RelativeTriggerNameValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FEventMaster::TypeName = "EventMaster";
}