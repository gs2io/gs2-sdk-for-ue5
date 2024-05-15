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

#include "Guild/Model/Namespace.h"

namespace Gs2::Guild::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        JoinNotificationValue(nullptr),
        LeaveNotificationValue(nullptr),
        ChangeMemberNotificationValue(nullptr),
        ReceiveRequestNotificationValue(nullptr),
        RemoveRequestNotificationValue(nullptr),
        LogSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FNamespace::FNamespace(
        const FNamespace& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        JoinNotificationValue(From.JoinNotificationValue),
        LeaveNotificationValue(From.LeaveNotificationValue),
        ChangeMemberNotificationValue(From.ChangeMemberNotificationValue),
        ReceiveRequestNotificationValue(From.ReceiveRequestNotificationValue),
        RemoveRequestNotificationValue(From.RemoveRequestNotificationValue),
        LogSettingValue(From.LogSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FNamespace> FNamespace::WithNamespaceId(
        const TOptional<FString> NamespaceId
    )
    {
        this->NamespaceIdValue = NamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithJoinNotification(
        const TSharedPtr<FNotificationSetting> JoinNotification
    )
    {
        this->JoinNotificationValue = JoinNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLeaveNotification(
        const TSharedPtr<FNotificationSetting> LeaveNotification
    )
    {
        this->LeaveNotificationValue = LeaveNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangeMemberNotification(
        const TSharedPtr<FNotificationSetting> ChangeMemberNotification
    )
    {
        this->ChangeMemberNotificationValue = ChangeMemberNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithReceiveRequestNotification(
        const TSharedPtr<FNotificationSetting> ReceiveRequestNotification
    )
    {
        this->ReceiveRequestNotificationValue = ReceiveRequestNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRemoveRequestNotification(
        const TSharedPtr<FNotificationSetting> RemoveRequestNotification
    )
    {
        this->RemoveRequestNotificationValue = RemoveRequestNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLogSetting(
        const TSharedPtr<FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FNamespace::GetNamespaceId() const
    {
        return NamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FNamespace::GetDescription() const
    {
        return DescriptionValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetJoinNotification() const
    {
        return JoinNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetLeaveNotification() const
    {
        return LeaveNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetChangeMemberNotification() const
    {
        return ChangeMemberNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetReceiveRequestNotification() const
    {
        return ReceiveRequestNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetRemoveRequestNotification() const
    {
        return RemoveRequestNotificationValue;
    }
    TSharedPtr<FLogSetting> FNamespace::GetLogSetting() const
    {
        return LogSettingValue;
    }
    TOptional<int64> FNamespace::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FNamespace::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FNamespace::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FNamespace::GetRevision() const
    {
        return RevisionValue;
    }

    FString FNamespace::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FNamespace::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FNamespace> FNamespace::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FNamespace>()
            ->WithNamespaceId(Data->HasField("namespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("namespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("description", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithJoinNotification(Data->HasField("joinNotification") ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("joinNotification"))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField("joinNotification"));
                 }() : nullptr)
            ->WithLeaveNotification(Data->HasField("leaveNotification") ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("leaveNotification"))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField("leaveNotification"));
                 }() : nullptr)
            ->WithChangeMemberNotification(Data->HasField("changeMemberNotification") ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("changeMemberNotification"))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField("changeMemberNotification"));
                 }() : nullptr)
            ->WithReceiveRequestNotification(Data->HasField("receiveRequestNotification") ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("receiveRequestNotification"))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField("receiveRequestNotification"));
                 }() : nullptr)
            ->WithRemoveRequestNotification(Data->HasField("removeRequestNotification") ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("removeRequestNotification"))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField("removeRequestNotification"));
                 }() : nullptr)
            ->WithLogSetting(Data->HasField("logSetting") ? [Data]() -> Model::FLogSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("logSetting"))
                    {
                        return nullptr;
                    }
                    return Model::FLogSetting::FromJson(Data->GetObjectField("logSetting"));
                 }() : nullptr)
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
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField("revision") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("revision", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FNamespace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceId", NamespaceIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (JoinNotificationValue != nullptr && JoinNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("joinNotification", JoinNotificationValue->ToJson());
        }
        if (LeaveNotificationValue != nullptr && LeaveNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("leaveNotification", LeaveNotificationValue->ToJson());
        }
        if (ChangeMemberNotificationValue != nullptr && ChangeMemberNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeMemberNotification", ChangeMemberNotificationValue->ToJson());
        }
        if (ReceiveRequestNotificationValue != nullptr && ReceiveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("receiveRequestNotification", ReceiveRequestNotificationValue->ToJson());
        }
        if (RemoveRequestNotificationValue != nullptr && RemoveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("removeRequestNotification", RemoveRequestNotificationValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
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
        return JsonRootObject;
    }

    FString FNamespace::TypeName = "Namespace";
}