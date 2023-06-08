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

#include "Schedule/Request/UpdateEventMasterRequest.h"

namespace Gs2::Schedule::Request
{
    FUpdateEventMasterRequest::FUpdateEventMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        EventNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ScheduleTypeValue(TOptional<FString>()),
        AbsoluteBeginValue(TOptional<int64>()),
        AbsoluteEndValue(TOptional<int64>()),
        RepeatTypeValue(TOptional<FString>()),
        RepeatBeginDayOfMonthValue(TOptional<int32>()),
        RepeatEndDayOfMonthValue(TOptional<int32>()),
        RepeatBeginDayOfWeekValue(TOptional<FString>()),
        RepeatEndDayOfWeekValue(TOptional<FString>()),
        RepeatBeginHourValue(TOptional<int32>()),
        RepeatEndHourValue(TOptional<int32>()),
        RelativeTriggerNameValue(TOptional<FString>())
    {
    }

    FUpdateEventMasterRequest::FUpdateEventMasterRequest(
        const FUpdateEventMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        EventNameValue(From.EventNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ScheduleTypeValue(From.ScheduleTypeValue),
        AbsoluteBeginValue(From.AbsoluteBeginValue),
        AbsoluteEndValue(From.AbsoluteEndValue),
        RepeatTypeValue(From.RepeatTypeValue),
        RepeatBeginDayOfMonthValue(From.RepeatBeginDayOfMonthValue),
        RepeatEndDayOfMonthValue(From.RepeatEndDayOfMonthValue),
        RepeatBeginDayOfWeekValue(From.RepeatBeginDayOfWeekValue),
        RepeatEndDayOfWeekValue(From.RepeatEndDayOfWeekValue),
        RepeatBeginHourValue(From.RepeatBeginHourValue),
        RepeatEndHourValue(From.RepeatEndHourValue),
        RelativeTriggerNameValue(From.RelativeTriggerNameValue)
    {
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithEventName(
        const TOptional<FString> EventName
    )
    {
        this->EventNameValue = EventName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithScheduleType(
        const TOptional<FString> ScheduleType
    )
    {
        this->ScheduleTypeValue = ScheduleType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithAbsoluteBegin(
        const TOptional<int64> AbsoluteBegin
    )
    {
        this->AbsoluteBeginValue = AbsoluteBegin;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithAbsoluteEnd(
        const TOptional<int64> AbsoluteEnd
    )
    {
        this->AbsoluteEndValue = AbsoluteEnd;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRepeatType(
        const TOptional<FString> RepeatType
    )
    {
        this->RepeatTypeValue = RepeatType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRepeatBeginDayOfMonth(
        const TOptional<int32> RepeatBeginDayOfMonth
    )
    {
        this->RepeatBeginDayOfMonthValue = RepeatBeginDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRepeatEndDayOfMonth(
        const TOptional<int32> RepeatEndDayOfMonth
    )
    {
        this->RepeatEndDayOfMonthValue = RepeatEndDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRepeatBeginDayOfWeek(
        const TOptional<FString> RepeatBeginDayOfWeek
    )
    {
        this->RepeatBeginDayOfWeekValue = RepeatBeginDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRepeatEndDayOfWeek(
        const TOptional<FString> RepeatEndDayOfWeek
    )
    {
        this->RepeatEndDayOfWeekValue = RepeatEndDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRepeatBeginHour(
        const TOptional<int32> RepeatBeginHour
    )
    {
        this->RepeatBeginHourValue = RepeatBeginHour;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRepeatEndHour(
        const TOptional<int32> RepeatEndHour
    )
    {
        this->RepeatEndHourValue = RepeatEndHour;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::WithRelativeTriggerName(
        const TOptional<FString> RelativeTriggerName
    )
    {
        this->RelativeTriggerNameValue = RelativeTriggerName;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateEventMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateEventMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateEventMasterRequest::GetEventName() const
    {
        return EventNameValue;
    }

    TOptional<FString> FUpdateEventMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateEventMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateEventMasterRequest::GetScheduleType() const
    {
        return ScheduleTypeValue;
    }

    TOptional<int64> FUpdateEventMasterRequest::GetAbsoluteBegin() const
    {
        return AbsoluteBeginValue;
    }

    FString FUpdateEventMasterRequest::GetAbsoluteBeginString() const
    {
        if (!AbsoluteBeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteBeginValue.GetValue());
    }

    TOptional<int64> FUpdateEventMasterRequest::GetAbsoluteEnd() const
    {
        return AbsoluteEndValue;
    }

    FString FUpdateEventMasterRequest::GetAbsoluteEndString() const
    {
        if (!AbsoluteEndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteEndValue.GetValue());
    }

    TOptional<FString> FUpdateEventMasterRequest::GetRepeatType() const
    {
        return RepeatTypeValue;
    }

    TOptional<int32> FUpdateEventMasterRequest::GetRepeatBeginDayOfMonth() const
    {
        return RepeatBeginDayOfMonthValue;
    }

    FString FUpdateEventMasterRequest::GetRepeatBeginDayOfMonthString() const
    {
        if (!RepeatBeginDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatBeginDayOfMonthValue.GetValue());
    }

    TOptional<int32> FUpdateEventMasterRequest::GetRepeatEndDayOfMonth() const
    {
        return RepeatEndDayOfMonthValue;
    }

    FString FUpdateEventMasterRequest::GetRepeatEndDayOfMonthString() const
    {
        if (!RepeatEndDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatEndDayOfMonthValue.GetValue());
    }

    TOptional<FString> FUpdateEventMasterRequest::GetRepeatBeginDayOfWeek() const
    {
        return RepeatBeginDayOfWeekValue;
    }

    TOptional<FString> FUpdateEventMasterRequest::GetRepeatEndDayOfWeek() const
    {
        return RepeatEndDayOfWeekValue;
    }

    TOptional<int32> FUpdateEventMasterRequest::GetRepeatBeginHour() const
    {
        return RepeatBeginHourValue;
    }

    FString FUpdateEventMasterRequest::GetRepeatBeginHourString() const
    {
        if (!RepeatBeginHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatBeginHourValue.GetValue());
    }

    TOptional<int32> FUpdateEventMasterRequest::GetRepeatEndHour() const
    {
        return RepeatEndHourValue;
    }

    FString FUpdateEventMasterRequest::GetRepeatEndHourString() const
    {
        if (!RepeatEndHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatEndHourValue.GetValue());
    }

    TOptional<FString> FUpdateEventMasterRequest::GetRelativeTriggerName() const
    {
        return RelativeTriggerNameValue;
    }

    TSharedPtr<FUpdateEventMasterRequest> FUpdateEventMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateEventMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithEventName(Data->HasField("eventName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("eventName", v))
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
            ->WithRepeatType(Data->HasField("repeatType") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("repeatType", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateEventMasterRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (EventNameValue.IsSet())
        {
            JsonRootObject->SetStringField("eventName", EventNameValue.GetValue());
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
        if (RelativeTriggerNameValue.IsSet())
        {
            JsonRootObject->SetStringField("relativeTriggerName", RelativeTriggerNameValue.GetValue());
        }
        return JsonRootObject;
    }
}