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

#include "Mission/Request/CreateMissionGroupModelMasterRequest.h"

namespace Gs2::Mission::Request
{
    FCreateMissionGroupModelMasterRequest::FCreateMissionGroupModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
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

    FCreateMissionGroupModelMasterRequest::FCreateMissionGroupModelMasterRequest(
        const FCreateMissionGroupModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
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

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithAnchorTimestamp(
        const TOptional<int64> AnchorTimestamp
    )
    {
        this->AnchorTimestampValue = AnchorTimestamp;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithDays(
        const TOptional<int32> Days
    )
    {
        this->DaysValue = Days;
        return SharedThis(this);
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::WithCompleteNotificationNamespaceId(
        const TOptional<FString> CompleteNotificationNamespaceId
    )
    {
        this->CompleteNotificationNamespaceIdValue = CompleteNotificationNamespaceId;
        return SharedThis(this);
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetResetType() const
    {
        return ResetTypeValue;
    }

    TOptional<int32> FCreateMissionGroupModelMasterRequest::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FCreateMissionGroupModelMasterRequest::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }

    TOptional<int32> FCreateMissionGroupModelMasterRequest::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FCreateMissionGroupModelMasterRequest::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }

    TOptional<int64> FCreateMissionGroupModelMasterRequest::GetAnchorTimestamp() const
    {
        return AnchorTimestampValue;
    }

    FString FCreateMissionGroupModelMasterRequest::GetAnchorTimestampString() const
    {
        if (!AnchorTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AnchorTimestampValue.GetValue());
    }

    TOptional<int32> FCreateMissionGroupModelMasterRequest::GetDays() const
    {
        return DaysValue;
    }

    FString FCreateMissionGroupModelMasterRequest::GetDaysString() const
    {
        if (!DaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DaysValue.GetValue());
    }

    TOptional<FString> FCreateMissionGroupModelMasterRequest::GetCompleteNotificationNamespaceId() const
    {
        return CompleteNotificationNamespaceIdValue;
    }

    TSharedPtr<FCreateMissionGroupModelMasterRequest> FCreateMissionGroupModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateMissionGroupModelMasterRequest>()
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

    TSharedPtr<FJsonObject> FCreateMissionGroupModelMasterRequest::ToJson() const
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