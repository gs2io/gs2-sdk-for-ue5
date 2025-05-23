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

#include "Mission/Model/MissionGroupModel.h"

namespace Gs2::Mission::Model
{
    FMissionGroupModel::FMissionGroupModel():
        MissionGroupIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TasksValue(nullptr),
        ResetTypeValue(TOptional<FString>()),
        ResetDayOfMonthValue(TOptional<int32>()),
        ResetDayOfWeekValue(TOptional<FString>()),
        ResetHourValue(TOptional<int32>()),
        CompleteNotificationNamespaceIdValue(TOptional<FString>()),
        AnchorTimestampValue(TOptional<int64>()),
        DaysValue(TOptional<int32>())
    {
    }

    FMissionGroupModel::FMissionGroupModel(
        const FMissionGroupModel& From
    ):
        MissionGroupIdValue(From.MissionGroupIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        TasksValue(From.TasksValue),
        ResetTypeValue(From.ResetTypeValue),
        ResetDayOfMonthValue(From.ResetDayOfMonthValue),
        ResetDayOfWeekValue(From.ResetDayOfWeekValue),
        ResetHourValue(From.ResetHourValue),
        CompleteNotificationNamespaceIdValue(From.CompleteNotificationNamespaceIdValue),
        AnchorTimestampValue(From.AnchorTimestampValue),
        DaysValue(From.DaysValue)
    {
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithMissionGroupId(
        const TOptional<FString> MissionGroupId
    )
    {
        this->MissionGroupIdValue = MissionGroupId;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithTasks(
        const TSharedPtr<TArray<TSharedPtr<Model::FMissionTaskModel>>> Tasks
    )
    {
        this->TasksValue = Tasks;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithResetType(
        const TOptional<FString> ResetType
    )
    {
        this->ResetTypeValue = ResetType;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithResetDayOfMonth(
        const TOptional<int32> ResetDayOfMonth
    )
    {
        this->ResetDayOfMonthValue = ResetDayOfMonth;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithResetDayOfWeek(
        const TOptional<FString> ResetDayOfWeek
    )
    {
        this->ResetDayOfWeekValue = ResetDayOfWeek;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithResetHour(
        const TOptional<int32> ResetHour
    )
    {
        this->ResetHourValue = ResetHour;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithCompleteNotificationNamespaceId(
        const TOptional<FString> CompleteNotificationNamespaceId
    )
    {
        this->CompleteNotificationNamespaceIdValue = CompleteNotificationNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithAnchorTimestamp(
        const TOptional<int64> AnchorTimestamp
    )
    {
        this->AnchorTimestampValue = AnchorTimestamp;
        return SharedThis(this);
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::WithDays(
        const TOptional<int32> Days
    )
    {
        this->DaysValue = Days;
        return SharedThis(this);
    }
    TOptional<FString> FMissionGroupModel::GetMissionGroupId() const
    {
        return MissionGroupIdValue;
    }
    TOptional<FString> FMissionGroupModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FMissionGroupModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FMissionTaskModel>>> FMissionGroupModel::GetTasks() const
    {
        return TasksValue;
    }
    TOptional<FString> FMissionGroupModel::GetResetType() const
    {
        return ResetTypeValue;
    }
    TOptional<int32> FMissionGroupModel::GetResetDayOfMonth() const
    {
        return ResetDayOfMonthValue;
    }

    FString FMissionGroupModel::GetResetDayOfMonthString() const
    {
        if (!ResetDayOfMonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetDayOfMonthValue.GetValue());
    }
    TOptional<FString> FMissionGroupModel::GetResetDayOfWeek() const
    {
        return ResetDayOfWeekValue;
    }
    TOptional<int32> FMissionGroupModel::GetResetHour() const
    {
        return ResetHourValue;
    }

    FString FMissionGroupModel::GetResetHourString() const
    {
        if (!ResetHourValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), ResetHourValue.GetValue());
    }
    TOptional<FString> FMissionGroupModel::GetCompleteNotificationNamespaceId() const
    {
        return CompleteNotificationNamespaceIdValue;
    }
    TOptional<int64> FMissionGroupModel::GetAnchorTimestamp() const
    {
        return AnchorTimestampValue;
    }

    FString FMissionGroupModel::GetAnchorTimestampString() const
    {
        if (!AnchorTimestampValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), AnchorTimestampValue.GetValue());
    }
    TOptional<int32> FMissionGroupModel::GetDays() const
    {
        return DaysValue;
    }

    FString FMissionGroupModel::GetDaysString() const
    {
        if (!DaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DaysValue.GetValue());
    }

    TOptional<FString> FMissionGroupModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionGroupModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionGroupModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FMissionGroupModel::GetMissionGroupNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):mission:(?<namespaceName>.+):group:(?<missionGroupName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FMissionGroupModel> FMissionGroupModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FMissionGroupModel>()
            ->WithMissionGroupId(Data->HasField(ANSI_TO_TCHAR("missionGroupId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("missionGroupId"), v))
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
            ->WithTasks(Data->HasField(ANSI_TO_TCHAR("tasks")) ? [Data]() -> TSharedPtr<TArray<Model::FMissionTaskModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FMissionTaskModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("tasks")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("tasks")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("tasks")))
                        {
                            v->Add(Model::FMissionTaskModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FMissionTaskModelPtr>>())
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
            ->WithCompleteNotificationNamespaceId(Data->HasField(ANSI_TO_TCHAR("completeNotificationNamespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("completeNotificationNamespaceId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
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
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FMissionGroupModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MissionGroupIdValue.IsSet())
        {
            JsonRootObject->SetStringField("missionGroupId", MissionGroupIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (TasksValue != nullptr && TasksValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TasksValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("tasks", v);
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
        if (CompleteNotificationNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("completeNotificationNamespaceId", CompleteNotificationNamespaceIdValue.GetValue());
        }
        if (AnchorTimestampValue.IsSet())
        {
            JsonRootObject->SetStringField("anchorTimestamp", FString::Printf(TEXT("%lld"), AnchorTimestampValue.GetValue()));
        }
        if (DaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("days", DaysValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FMissionGroupModel::TypeName = "MissionGroupModel";
}