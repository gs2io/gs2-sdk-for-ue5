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

#include "EzGs2/Public/Schedule/Model/Gs2ScheduleEzEvent.h"

namespace Gs2::UE5::Schedule::Model
{

    TSharedPtr<FEzEvent> FEzEvent::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithScheduleType(
        const TOptional<FString> ScheduleType
    )
    {
        this->ScheduleTypeValue = ScheduleType;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRepeatType(
        const TOptional<FString> RepeatType
    )
    {
        this->RepeatTypeValue = RepeatType;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithAbsoluteBegin(
        const TOptional<int64> AbsoluteBegin
    )
    {
        this->AbsoluteBeginValue = AbsoluteBegin;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithAbsoluteEnd(
        const TOptional<int64> AbsoluteEnd
    )
    {
        this->AbsoluteEndValue = AbsoluteEnd;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRepeatBeginDayOfMonth(
        const TOptional<int32> RepeatBeginDayOfMonth
    )
    {
        this->RepeatBeginDayOfMonthValue = RepeatBeginDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRepeatEndDayOfMonth(
        const TOptional<int32> RepeatEndDayOfMonth
    )
    {
        this->RepeatEndDayOfMonthValue = RepeatEndDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRepeatBeginDayOfWeek(
        const TOptional<FString> RepeatBeginDayOfWeek
    )
    {
        this->RepeatBeginDayOfWeekValue = RepeatBeginDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRepeatEndDayOfWeek(
        const TOptional<FString> RepeatEndDayOfWeek
    )
    {
        this->RepeatEndDayOfWeekValue = RepeatEndDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRepeatBeginHour(
        const TOptional<int32> RepeatBeginHour
    )
    {
        this->RepeatBeginHourValue = RepeatBeginHour;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRepeatEndHour(
        const TOptional<int32> RepeatEndHour
    )
    {
        this->RepeatEndHourValue = RepeatEndHour;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRelativeTriggerName(
        const TOptional<FString> RelativeTriggerName
    )
    {
        this->RelativeTriggerNameValue = RelativeTriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FEzEvent> FEzEvent::WithRelativeDuration(
        const TOptional<int32> RelativeDuration
    )
    {
        this->RelativeDurationValue = RelativeDuration;
        return SharedThis(this);
    }
    TOptional<FString> FEzEvent::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzEvent::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzEvent::GetScheduleType() const
    {
        return ScheduleTypeValue;
    }
    TOptional<FString> FEzEvent::GetRepeatType() const
    {
        return RepeatTypeValue;
    }
    TOptional<int64> FEzEvent::GetAbsoluteBegin() const
    {
        return AbsoluteBeginValue;
    }

    FString FEzEvent::GetAbsoluteBeginString() const
    {
        if (!AbsoluteBeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteBeginValue.GetValue());
    }
    TOptional<int64> FEzEvent::GetAbsoluteEnd() const
    {
        return AbsoluteEndValue;
    }

    FString FEzEvent::GetAbsoluteEndString() const
    {
        if (!AbsoluteEndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteEndValue.GetValue());
    }
    TOptional<int32> FEzEvent::GetRepeatBeginDayOfMonth() const
    {
        return RepeatBeginDayOfMonthValue;
    }

    FString FEzEvent::GetRepeatBeginDayOfMonthString() const
    {
        if (!RepeatBeginDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), RepeatBeginDayOfMonthValue.GetValue());
    }
    TOptional<int32> FEzEvent::GetRepeatEndDayOfMonth() const
    {
        return RepeatEndDayOfMonthValue;
    }

    FString FEzEvent::GetRepeatEndDayOfMonthString() const
    {
        if (!RepeatEndDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), RepeatEndDayOfMonthValue.GetValue());
    }
    TOptional<FString> FEzEvent::GetRepeatBeginDayOfWeek() const
    {
        return RepeatBeginDayOfWeekValue;
    }
    TOptional<FString> FEzEvent::GetRepeatEndDayOfWeek() const
    {
        return RepeatEndDayOfWeekValue;
    }
    TOptional<int32> FEzEvent::GetRepeatBeginHour() const
    {
        return RepeatBeginHourValue;
    }

    FString FEzEvent::GetRepeatBeginHourString() const
    {
        if (!RepeatBeginHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), RepeatBeginHourValue.GetValue());
    }
    TOptional<int32> FEzEvent::GetRepeatEndHour() const
    {
        return RepeatEndHourValue;
    }

    FString FEzEvent::GetRepeatEndHourString() const
    {
        if (!RepeatEndHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), RepeatEndHourValue.GetValue());
    }
    TOptional<FString> FEzEvent::GetRelativeTriggerName() const
    {
        return RelativeTriggerNameValue;
    }
    TOptional<int32> FEzEvent::GetRelativeDuration() const
    {
        return RelativeDurationValue;
    }

    FString FEzEvent::GetRelativeDurationString() const
    {
        if (!RelativeDurationValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), RelativeDurationValue.GetValue());
    }

    Gs2::Schedule::Model::FEventPtr FEzEvent::ToModel() const
    {
        return MakeShared<Gs2::Schedule::Model::FEvent>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithScheduleType(ScheduleTypeValue)
            ->WithRepeatType(RepeatTypeValue)
            ->WithAbsoluteBegin(AbsoluteBeginValue)
            ->WithAbsoluteEnd(AbsoluteEndValue)
            ->WithRepeatBeginDayOfMonth(RepeatBeginDayOfMonthValue)
            ->WithRepeatEndDayOfMonth(RepeatEndDayOfMonthValue)
            ->WithRepeatBeginDayOfWeek(RepeatBeginDayOfWeekValue)
            ->WithRepeatEndDayOfWeek(RepeatEndDayOfWeekValue)
            ->WithRepeatBeginHour(RepeatBeginHourValue)
            ->WithRepeatEndHour(RepeatEndHourValue)
            ->WithRelativeTriggerName(RelativeTriggerNameValue)
            ->WithRelativeDuration(RelativeDurationValue);
    }

    TSharedPtr<FEzEvent> FEzEvent::FromModel(const Gs2::Schedule::Model::FEventPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzEvent>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithScheduleType(Model->GetScheduleType())
            ->WithRepeatType(Model->GetRepeatType())
            ->WithAbsoluteBegin(Model->GetAbsoluteBegin())
            ->WithAbsoluteEnd(Model->GetAbsoluteEnd())
            ->WithRepeatBeginDayOfMonth(Model->GetRepeatBeginDayOfMonth())
            ->WithRepeatEndDayOfMonth(Model->GetRepeatEndDayOfMonth())
            ->WithRepeatBeginDayOfWeek(Model->GetRepeatBeginDayOfWeek())
            ->WithRepeatEndDayOfWeek(Model->GetRepeatEndDayOfWeek())
            ->WithRepeatBeginHour(Model->GetRepeatBeginHour())
            ->WithRepeatEndHour(Model->GetRepeatEndHour())
            ->WithRelativeTriggerName(Model->GetRelativeTriggerName())
            ->WithRelativeDuration(Model->GetRelativeDuration());
    }
}