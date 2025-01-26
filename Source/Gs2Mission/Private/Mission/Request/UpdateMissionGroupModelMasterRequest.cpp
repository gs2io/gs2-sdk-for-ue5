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

#include "Mission/Request/UpdateMissionGroupModelMasterRequest.h"

namespace Gs2::Mission::Request
{
    FUpdateMissionGroupModelMasterRequest::FUpdateMissionGroupModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        MissionGroupNameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ResetTypeValue(TOptional<FString>()),
        ResetDayOfMonthValue(TOptional<int32>()),
        ResetDayOfWeekValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>()),
        AnchorTimestampValue(TOptional<int64>()),
        DaysValue(TOptional<int32>()),
        CompleteNotificationNamespaceIdValue(TOptional<FString>())
    {
    }

    FUpdateMissionGroupModelMasterRequest::FUpdateMissionGroupModelMasterRequest(
        const FUpdateMissionGroupModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        MissionGroupNameValue(From.MissionGroupNameValue),
        MetadataValue(From.MetadataValue),
        DescriptionValue(From.DescriptionValue),
        ResetTypeValue(From.ResetTypeValue),
        ResetDayOfMonthValue(From.ResetDayOfMonthValue),
        ResetDayOfWeekValue(From.ResetDayOfWeekValue),
        ResetHourValue(From.ResetHourValue),
        AnchorTimestampValue(From.AnchorTimestampValue),
        DaysValue(From.DaysValue),
        CompleteNotificationNamespaceIdValue(From.CompleteNotificationNamespaceIdValue)
    {
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithAnchorTimestamp(
        const TOptional<int64> AnchorTimestamp
    )
    {
        this->AnchorTimestampValue = AnchorTimestamp;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithDays(
        const TOptional<int32> Days
    )
    {
        this->DaysValue = Days;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::WithCompleteNotificationNamespaceId(
        const TOptional<FString> CompleteNotificationNamespaceId
    )
    {
        this->CompleteNotificationNamespaceIdValue = CompleteNotificationNamespaceId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetResetType() const
    {
        return ResetTypeValue;
    }

    TOptional<int32> FUpdateMissionGroupModelMasterRequest::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FUpdateMissionGroupModelMasterRequest::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }

    TOptional<int32> FUpdateMissionGroupModelMasterRequest::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FUpdateMissionGroupModelMasterRequest::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }

    TOptional<int64> FUpdateMissionGroupModelMasterRequest::GetAnchorTimestamp() const
    {
        return AnchorTimestampValue;
    }

    FString FUpdateMissionGroupModelMasterRequest::GetAnchorTimestampString() const
    {
        if (!AnchorTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AnchorTimestampValue.GetValue());
    }

    TOptional<int32> FUpdateMissionGroupModelMasterRequest::GetDays() const
    {
        return DaysValue;
    }

    FString FUpdateMissionGroupModelMasterRequest::GetDaysString() const
    {
        if (!DaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DaysValue.GetValue());
    }

    TOptional<FString> FUpdateMissionGroupModelMasterRequest::GetCompleteNotificationNamespaceId() const
    {
        return CompleteNotificationNamespaceIdValue;
    }

    TSharedPtr<FUpdateMissionGroupModelMasterRequest> FUpdateMissionGroupModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateMissionGroupModelMasterRequest>()
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
            ->WithMissionGroupName(Data->HasField(ANSI_TO_TCHAR("missionGroupName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("missionGroupName"), v))
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
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetType(Data->HasField(ANSI_TO_TCHAR("resetType")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("resetType"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetDayOfMonth(Data->HasField(ANSI_TO_TCHAR("resetDayOfMonth")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("resetDayOfMonth"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithResetDayOfWeek(Data->HasField(ANSI_TO_TCHAR("resetDayOfWeek")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("resetDayOfWeek"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithResetHour(Data->HasField(ANSI_TO_TCHAR("resetHour")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("resetHour"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithAnchorTimestamp(Data->HasField(ANSI_TO_TCHAR("anchorTimestamp")) ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("anchorTimestamp"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithDays(Data->HasField(ANSI_TO_TCHAR("days")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("days"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithCompleteNotificationNamespaceId(Data->HasField(ANSI_TO_TCHAR("completeNotificationNamespaceId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("completeNotificationNamespaceId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateMissionGroupModelMasterRequest::ToJson() const
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
        if (MissionGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("missionGroupName", MissionGroupNameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (ResetTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("resetType", ResetTypeValue.GetValue());
        }
        if (ResetDayOfMonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetDayOfMonth", ResetDayOfMonthValue.GetValue());
        }
        if (ResetDayOfWeekValue.IsSet())
        {
            JsonRootObject->SetStringField("resetDayOfWeek", ResetDayOfWeekValue.GetValue());
        }
        if (ResetHourValue.IsSet())
        {
            JsonRootObject->SetNumberField("resetHour", ResetHourValue.GetValue());
        }
        if (AnchorTimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("anchorTimestamp", FString::Printf(TEXT("%lld"), AnchorTimestampValue.GetValue()));
        }
        if (DaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("days", DaysValue.GetValue());
        }
        if (CompleteNotificationNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completeNotificationNamespaceId", CompleteNotificationNamespaceIdValue.GetValue());
        }
        return JsonRootObject;
    }
}