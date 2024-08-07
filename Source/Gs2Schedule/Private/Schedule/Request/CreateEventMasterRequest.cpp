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

#include "Schedule/Request/CreateEventMasterRequest.h"

namespace Gs2::Schedule::Request
{
    FCreateEventMasterRequest::FCreateEventMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
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
        RelativeTriggerNameValue(TOptional<FString>()),
        RepeatSettingValue(nullptr)
    {
    }

    FCreateEventMasterRequest::FCreateEventMasterRequest(
        const FCreateEventMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
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
        RelativeTriggerNameValue(From.RelativeTriggerNameValue),
        RepeatSettingValue(From.RepeatSettingValue)
    {
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithScheduleType(
        const TOptional<FString> ScheduleType
    )
    {
        this->ScheduleTypeValue = ScheduleType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithAbsoluteBegin(
        const TOptional<int64> AbsoluteBegin
    )
    {
        this->AbsoluteBeginValue = AbsoluteBegin;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithAbsoluteEnd(
        const TOptional<int64> AbsoluteEnd
    )
    {
        this->AbsoluteEndValue = AbsoluteEnd;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatType(
        const TOptional<FString> RepeatType
    )
    {
        this->RepeatTypeValue = RepeatType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatBeginDayOfMonth(
        const TOptional<int32> RepeatBeginDayOfMonth
    )
    {
        this->RepeatBeginDayOfMonthValue = RepeatBeginDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatEndDayOfMonth(
        const TOptional<int32> RepeatEndDayOfMonth
    )
    {
        this->RepeatEndDayOfMonthValue = RepeatEndDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatBeginDayOfWeek(
        const TOptional<FString> RepeatBeginDayOfWeek
    )
    {
        this->RepeatBeginDayOfWeekValue = RepeatBeginDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatEndDayOfWeek(
        const TOptional<FString> RepeatEndDayOfWeek
    )
    {
        this->RepeatEndDayOfWeekValue = RepeatEndDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatBeginHour(
        const TOptional<int32> RepeatBeginHour
    )
    {
        this->RepeatBeginHourValue = RepeatBeginHour;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatEndHour(
        const TOptional<int32> RepeatEndHour
    )
    {
        this->RepeatEndHourValue = RepeatEndHour;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRelativeTriggerName(
        const TOptional<FString> RelativeTriggerName
    )
    {
        this->RelativeTriggerNameValue = RelativeTriggerName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::WithRepeatSetting(
        const TSharedPtr<Model::FRepeatSetting> RepeatSetting
    )
    {
        this->RepeatSettingValue = RepeatSetting;
        return SharedThis(this);
    }

    TOptional<FString> FCreateEventMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateEventMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateEventMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateEventMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateEventMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FCreateEventMasterRequest::GetScheduleType() const
    {
        return ScheduleTypeValue;
    }

    TOptional<int64> FCreateEventMasterRequest::GetAbsoluteBegin() const
    {
        return AbsoluteBeginValue;
    }

    FString FCreateEventMasterRequest::GetAbsoluteBeginString() const
    {
        if (!AbsoluteBeginValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteBeginValue.GetValue());
    }

    TOptional<int64> FCreateEventMasterRequest::GetAbsoluteEnd() const
    {
        return AbsoluteEndValue;
    }

    FString FCreateEventMasterRequest::GetAbsoluteEndString() const
    {
        if (!AbsoluteEndValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AbsoluteEndValue.GetValue());
    }

    TOptional<FString> FCreateEventMasterRequest::GetRepeatType() const
    {
        return RepeatTypeValue;
    }

    TOptional<int32> FCreateEventMasterRequest::GetRepeatBeginDayOfMonth() const
    {
        return RepeatBeginDayOfMonthValue;
    }

    FString FCreateEventMasterRequest::GetRepeatBeginDayOfMonthString() const
    {
        if (!RepeatBeginDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatBeginDayOfMonthValue.GetValue());
    }

    TOptional<int32> FCreateEventMasterRequest::GetRepeatEndDayOfMonth() const
    {
        return RepeatEndDayOfMonthValue;
    }

    FString FCreateEventMasterRequest::GetRepeatEndDayOfMonthString() const
    {
        if (!RepeatEndDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatEndDayOfMonthValue.GetValue());
    }

    TOptional<FString> FCreateEventMasterRequest::GetRepeatBeginDayOfWeek() const
    {
        return RepeatBeginDayOfWeekValue;
    }

    TOptional<FString> FCreateEventMasterRequest::GetRepeatEndDayOfWeek() const
    {
        return RepeatEndDayOfWeekValue;
    }

    TOptional<int32> FCreateEventMasterRequest::GetRepeatBeginHour() const
    {
        return RepeatBeginHourValue;
    }

    FString FCreateEventMasterRequest::GetRepeatBeginHourString() const
    {
        if (!RepeatBeginHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatBeginHourValue.GetValue());
    }

    TOptional<int32> FCreateEventMasterRequest::GetRepeatEndHour() const
    {
        return RepeatEndHourValue;
    }

    FString FCreateEventMasterRequest::GetRepeatEndHourString() const
    {
        if (!RepeatEndHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RepeatEndHourValue.GetValue());
    }

    TOptional<FString> FCreateEventMasterRequest::GetRelativeTriggerName() const
    {
        return RelativeTriggerNameValue;
    }

    TSharedPtr<Model::FRepeatSetting> FCreateEventMasterRequest::GetRepeatSetting() const
    {
        if (!RepeatSettingValue.IsValid())
        {
            return nullptr;
        }
        return RepeatSettingValue;
    }

    TSharedPtr<FCreateEventMasterRequest> FCreateEventMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateEventMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
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
              }() : TOptional<int32>())
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
              }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateEventMasterRequest::ToJson() const
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
        if (RepeatSettingValue != nullptr && RepeatSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("repeatSetting", RepeatSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}