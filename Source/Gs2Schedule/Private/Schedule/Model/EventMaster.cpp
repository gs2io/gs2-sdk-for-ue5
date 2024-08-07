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
        AbsoluteBeginValue(TOptional<int64>()),
        AbsoluteEndValue(TOptional<int64>()),
        RelativeTriggerNameValue(TOptional<FString>()),
        RepeatSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>()),
        RepeatTypeValue(TOptional<FString>()),
        RepeatBeginDayOfMonthValue(TOptional<int32>()),
        RepeatEndDayOfMonthValue(TOptional<int32>()),
        RepeatBeginDayOfWeekValue(TOptional<FString>()),
        RepeatEndDayOfWeekValue(TOptional<FString>()),
        RepeatBeginHourValue(TOptional<int32>()),
        RepeatEndHourValue(TOptional<int32>())
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
        AbsoluteBeginValue(From.AbsoluteBeginValue),
        AbsoluteEndValue(From.AbsoluteEndValue),
        RelativeTriggerNameValue(From.RelativeTriggerNameValue),
        RepeatSettingValue(From.RepeatSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue),
        RepeatTypeValue(From.RepeatTypeValue),
        RepeatBeginDayOfMonthValue(From.RepeatBeginDayOfMonthValue),
        RepeatEndDayOfMonthValue(From.RepeatEndDayOfMonthValue),
        RepeatBeginDayOfWeekValue(From.RepeatBeginDayOfWeekValue),
        RepeatEndDayOfWeekValue(From.RepeatEndDayOfWeekValue),
        RepeatBeginHourValue(From.RepeatBeginHourValue),
        RepeatEndHourValue(From.RepeatEndHourValue)
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

    TSharedPtr<FEventMaster> FEventMaster::WithRelativeTriggerName(
        const TOptional<FString> RelativeTriggerName
    )
    {
        this->RelativeTriggerNameValue = RelativeTriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatSetting(
        const TSharedPtr<FRepeatSetting> RepeatSetting
    )
    {
        this->RepeatSettingValue = RepeatSetting;
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

    TSharedPtr<FEventMaster> FEventMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }

    TSharedPtr<FEventMaster> FEventMaster::WithRepeatType(
        const TOptional<FString> RepeatType
    )
    {
        this->RepeatTypeValue = RepeatType;
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
    TOptional<FString> FEventMaster::GetRelativeTriggerName() const
    {
        return RelativeTriggerNameValue;
    }
    TSharedPtr<FRepeatSetting> FEventMaster::GetRepeatSetting() const
    {
        return RepeatSettingValue;
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
    TOptional<int64> FEventMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FEventMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }
    TOptional<FString> FEventMaster::GetRepeatType() const
    {
        return RepeatTypeValue;
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
            ->WithEventId(Data->HasField(ANSI_TO_TCHAR("eventId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("eventId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScheduleType(Data->HasField(ANSI_TO_TCHAR("scheduleType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("scheduleType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAbsoluteBegin(Data->HasField(ANSI_TO_TCHAR("absoluteBegin")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("absoluteBegin"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithAbsoluteEnd(Data->HasField(ANSI_TO_TCHAR("absoluteEnd")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("absoluteEnd"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRelativeTriggerName(Data->HasField(ANSI_TO_TCHAR("relativeTriggerName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("relativeTriggerName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepeatSetting(Data->HasField(ANSI_TO_TCHAR("repeatSetting")) ? [Data]() -> Model::FRepeatSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("repeatSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FRepeatSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("repeatSetting")));
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRepeatType(Data->HasField(ANSI_TO_TCHAR("repeatType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("repeatType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepeatBeginDayOfMonth(Data->HasField(ANSI_TO_TCHAR("repeatBeginDayOfMonth")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("repeatBeginDayOfMonth"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRepeatEndDayOfMonth(Data->HasField(ANSI_TO_TCHAR("repeatEndDayOfMonth")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("repeatEndDayOfMonth"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRepeatBeginDayOfWeek(Data->HasField(ANSI_TO_TCHAR("repeatBeginDayOfWeek")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("repeatBeginDayOfWeek"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepeatEndDayOfWeek(Data->HasField(ANSI_TO_TCHAR("repeatEndDayOfWeek")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("repeatEndDayOfWeek"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepeatBeginHour(Data->HasField(ANSI_TO_TCHAR("repeatBeginHour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("repeatBeginHour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRepeatEndHour(Data->HasField(ANSI_TO_TCHAR("repeatEndHour")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("repeatEndHour"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
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
        if (AbsoluteBeginValue.IsSet())
        {
            JsonRootObject->SetStringField("absoluteBegin", FString::Printf(TEXT("%lld"), AbsoluteBeginValue.GetValue()));
        }
        if (AbsoluteEndValue.IsSet())
        {
            JsonRootObject->SetStringField("absoluteEnd", FString::Printf(TEXT("%lld"), AbsoluteEndValue.GetValue()));
        }
        if (RelativeTriggerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("relativeTriggerName", RelativeTriggerNameValue.GetValue());
        }
        if (RepeatSettingValue != nullptr && RepeatSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("repeatSetting", RepeatSettingValue->ToJson());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        if (RepeatTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("repeatType", RepeatTypeValue.GetValue());
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
        return JsonRootObject;
    }

    FString FEventMaster::TypeName = "EventMaster";
}