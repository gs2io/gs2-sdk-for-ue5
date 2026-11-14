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
        TransactionSettingValue(nullptr),
        TransactionSettingV2Value(nullptr),
        ChangeNotificationValue(nullptr),
        JoinNotificationValue(nullptr),
        LeaveNotificationValue(nullptr),
        ChangeMemberNotificationValue(nullptr),
        ChangeMemberNotificationIgnoreChangeMetadataValue(TOptional<bool>()),
        ReceiveRequestNotificationValue(nullptr),
        RemoveRequestNotificationValue(nullptr),
        CreateGuildScriptValue(nullptr),
        UpdateGuildScriptValue(nullptr),
        JoinGuildScriptValue(nullptr),
        ReceiveJoinRequestScriptValue(nullptr),
        LeaveGuildScriptValue(nullptr),
        ChangeRoleScriptValue(nullptr),
        DeleteGuildScriptValue(nullptr),
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
        TransactionSettingValue(From.TransactionSettingValue),
        TransactionSettingV2Value(From.TransactionSettingV2Value),
        ChangeNotificationValue(From.ChangeNotificationValue),
        JoinNotificationValue(From.JoinNotificationValue),
        LeaveNotificationValue(From.LeaveNotificationValue),
        ChangeMemberNotificationValue(From.ChangeMemberNotificationValue),
        ChangeMemberNotificationIgnoreChangeMetadataValue(From.ChangeMemberNotificationIgnoreChangeMetadataValue),
        ReceiveRequestNotificationValue(From.ReceiveRequestNotificationValue),
        RemoveRequestNotificationValue(From.RemoveRequestNotificationValue),
        CreateGuildScriptValue(From.CreateGuildScriptValue),
        UpdateGuildScriptValue(From.UpdateGuildScriptValue),
        JoinGuildScriptValue(From.JoinGuildScriptValue),
        ReceiveJoinRequestScriptValue(From.ReceiveJoinRequestScriptValue),
        LeaveGuildScriptValue(From.LeaveGuildScriptValue),
        ChangeRoleScriptValue(From.ChangeRoleScriptValue),
        DeleteGuildScriptValue(From.DeleteGuildScriptValue),
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

    TSharedPtr<FNamespace> FNamespace::WithTransactionSetting(
        const TSharedPtr<FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithTransactionSettingV2(
        const TSharedPtr<FTransactionSettingV2> TransactionSettingV2
    )
    {
        this->TransactionSettingV2Value = TransactionSettingV2;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangeNotification(
        const TSharedPtr<FNotificationSetting> ChangeNotification
    )
    {
        this->ChangeNotificationValue = ChangeNotification;
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

    TSharedPtr<FNamespace> FNamespace::WithChangeMemberNotificationIgnoreChangeMetadata(
        const TOptional<bool> ChangeMemberNotificationIgnoreChangeMetadata
    )
    {
        this->ChangeMemberNotificationIgnoreChangeMetadataValue = ChangeMemberNotificationIgnoreChangeMetadata;
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

    TSharedPtr<FNamespace> FNamespace::WithCreateGuildScript(
        const TSharedPtr<FScriptSetting> CreateGuildScript
    )
    {
        this->CreateGuildScriptValue = CreateGuildScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdateGuildScript(
        const TSharedPtr<FScriptSetting> UpdateGuildScript
    )
    {
        this->UpdateGuildScriptValue = UpdateGuildScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithJoinGuildScript(
        const TSharedPtr<FScriptSetting> JoinGuildScript
    )
    {
        this->JoinGuildScriptValue = JoinGuildScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithReceiveJoinRequestScript(
        const TSharedPtr<FScriptSetting> ReceiveJoinRequestScript
    )
    {
        this->ReceiveJoinRequestScriptValue = ReceiveJoinRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLeaveGuildScript(
        const TSharedPtr<FScriptSetting> LeaveGuildScript
    )
    {
        this->LeaveGuildScriptValue = LeaveGuildScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithChangeRoleScript(
        const TSharedPtr<FScriptSetting> ChangeRoleScript
    )
    {
        this->ChangeRoleScriptValue = ChangeRoleScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDeleteGuildScript(
        const TSharedPtr<FScriptSetting> DeleteGuildScript
    )
    {
        this->DeleteGuildScriptValue = DeleteGuildScript;
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
    TSharedPtr<FTransactionSetting> FNamespace::GetTransactionSetting() const
    {
        return TransactionSettingValue;
    }
    TSharedPtr<FTransactionSettingV2> FNamespace::GetTransactionSettingV2() const
    {
        return TransactionSettingV2Value;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetChangeNotification() const
    {
        return ChangeNotificationValue;
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
    TOptional<bool> FNamespace::GetChangeMemberNotificationIgnoreChangeMetadata() const
    {
        return ChangeMemberNotificationIgnoreChangeMetadataValue;
    }

    FString FNamespace::GetChangeMemberNotificationIgnoreChangeMetadataString() const
    {
        if (!ChangeMemberNotificationIgnoreChangeMetadataValue.IsSet())
        {
            return FString("null");
        }
        return FString(ChangeMemberNotificationIgnoreChangeMetadataValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetReceiveRequestNotification() const
    {
        return ReceiveRequestNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetRemoveRequestNotification() const
    {
        return RemoveRequestNotificationValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCreateGuildScript() const
    {
        return CreateGuildScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetUpdateGuildScript() const
    {
        return UpdateGuildScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetJoinGuildScript() const
    {
        return JoinGuildScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetReceiveJoinRequestScript() const
    {
        return ReceiveJoinRequestScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetLeaveGuildScript() const
    {
        return LeaveGuildScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetChangeRoleScript() const
    {
        return ChangeRoleScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetDeleteGuildScript() const
    {
        return DeleteGuildScriptValue;
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
            ->WithNamespaceId(Data->HasField(ANSI_TO_TCHAR("namespaceId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionSetting(Data->HasField(ANSI_TO_TCHAR("transactionSetting")) ? [Data]() -> Model::FTransactionSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSetting")));
                 }() : nullptr)
            ->WithTransactionSettingV2(Data->HasField(ANSI_TO_TCHAR("transactionSettingV2")) ? [Data]() -> Model::FTransactionSettingV2Ptr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSettingV2")))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionSettingV2::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSettingV2")));
                 }() : nullptr)
            ->WithChangeNotification(Data->HasField(ANSI_TO_TCHAR("changeNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeNotification")));
                 }() : nullptr)
            ->WithJoinNotification(Data->HasField(ANSI_TO_TCHAR("joinNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("joinNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("joinNotification")));
                 }() : nullptr)
            ->WithLeaveNotification(Data->HasField(ANSI_TO_TCHAR("leaveNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("leaveNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("leaveNotification")));
                 }() : nullptr)
            ->WithChangeMemberNotification(Data->HasField(ANSI_TO_TCHAR("changeMemberNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeMemberNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeMemberNotification")));
                 }() : nullptr)
            ->WithChangeMemberNotificationIgnoreChangeMetadata(Data->HasField(ANSI_TO_TCHAR("changeMemberNotificationIgnoreChangeMetadata")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("changeMemberNotificationIgnoreChangeMetadata"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithReceiveRequestNotification(Data->HasField(ANSI_TO_TCHAR("receiveRequestNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receiveRequestNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receiveRequestNotification")));
                 }() : nullptr)
            ->WithRemoveRequestNotification(Data->HasField(ANSI_TO_TCHAR("removeRequestNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("removeRequestNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("removeRequestNotification")));
                 }() : nullptr)
            ->WithCreateGuildScript(Data->HasField(ANSI_TO_TCHAR("createGuildScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("createGuildScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("createGuildScript")));
                 }() : nullptr)
            ->WithUpdateGuildScript(Data->HasField(ANSI_TO_TCHAR("updateGuildScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("updateGuildScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("updateGuildScript")));
                 }() : nullptr)
            ->WithJoinGuildScript(Data->HasField(ANSI_TO_TCHAR("joinGuildScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("joinGuildScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("joinGuildScript")));
                 }() : nullptr)
            ->WithReceiveJoinRequestScript(Data->HasField(ANSI_TO_TCHAR("receiveJoinRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receiveJoinRequestScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receiveJoinRequestScript")));
                 }() : nullptr)
            ->WithLeaveGuildScript(Data->HasField(ANSI_TO_TCHAR("leaveGuildScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("leaveGuildScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("leaveGuildScript")));
                 }() : nullptr)
            ->WithChangeRoleScript(Data->HasField(ANSI_TO_TCHAR("changeRoleScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeRoleScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeRoleScript")));
                 }() : nullptr)
            ->WithDeleteGuildScript(Data->HasField(ANSI_TO_TCHAR("deleteGuildScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("deleteGuildScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("deleteGuildScript")));
                 }() : nullptr)
            ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                    {
                        return nullptr;
                    }
                    return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
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
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FNamespace::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("namespaceId"), NamespaceIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("description"), DescriptionValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("transactionSetting"), TransactionSettingValue->ToJson());
        }
        if (TransactionSettingV2Value != nullptr && TransactionSettingV2Value.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("transactionSettingV2"), TransactionSettingV2Value->ToJson());
        }
        if (ChangeNotificationValue != nullptr && ChangeNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("changeNotification"), ChangeNotificationValue->ToJson());
        }
        if (JoinNotificationValue != nullptr && JoinNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("joinNotification"), JoinNotificationValue->ToJson());
        }
        if (LeaveNotificationValue != nullptr && LeaveNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("leaveNotification"), LeaveNotificationValue->ToJson());
        }
        if (ChangeMemberNotificationValue != nullptr && ChangeMemberNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("changeMemberNotification"), ChangeMemberNotificationValue->ToJson());
        }
        if (ChangeMemberNotificationIgnoreChangeMetadataValue.IsSet())
        {
            JsonRootObject->SetBoolField(TEXT("changeMemberNotificationIgnoreChangeMetadata"), ChangeMemberNotificationIgnoreChangeMetadataValue.GetValue());
        }
        if (ReceiveRequestNotificationValue != nullptr && ReceiveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("receiveRequestNotification"), ReceiveRequestNotificationValue->ToJson());
        }
        if (RemoveRequestNotificationValue != nullptr && RemoveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("removeRequestNotification"), RemoveRequestNotificationValue->ToJson());
        }
        if (CreateGuildScriptValue != nullptr && CreateGuildScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("createGuildScript"), CreateGuildScriptValue->ToJson());
        }
        if (UpdateGuildScriptValue != nullptr && UpdateGuildScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("updateGuildScript"), UpdateGuildScriptValue->ToJson());
        }
        if (JoinGuildScriptValue != nullptr && JoinGuildScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("joinGuildScript"), JoinGuildScriptValue->ToJson());
        }
        if (ReceiveJoinRequestScriptValue != nullptr && ReceiveJoinRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("receiveJoinRequestScript"), ReceiveJoinRequestScriptValue->ToJson());
        }
        if (LeaveGuildScriptValue != nullptr && LeaveGuildScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("leaveGuildScript"), LeaveGuildScriptValue->ToJson());
        }
        if (ChangeRoleScriptValue != nullptr && ChangeRoleScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("changeRoleScript"), ChangeRoleScriptValue->ToJson());
        }
        if (DeleteGuildScriptValue != nullptr && DeleteGuildScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("deleteGuildScript"), DeleteGuildScriptValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField(TEXT("logSetting"), LogSettingValue->ToJson());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("updatedAt"), FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FNamespace::TypeName = "Namespace";
}
#include "Guild/Model/Cache/Namespace.h"

namespace Gs2::Guild::Model::Cache
{
    FString FNamespaceCache::CreateCacheParentKey(
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("guild:")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":Namespace");
    }

    FString FNamespaceCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName
    )
    {
        return
            FString()
            + CacheOwnerArgumentNamespaceName.Get(FString())
            ;
    }

    bool FNamespaceCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Guild::Model::FNamespacePtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Guild::Model::FNamespacePtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Guild::Model::FNamespace>(
            CreateCacheParentKey(
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentNamespaceName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FNamespaceCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Guild::Model::FNamespacePtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentNamespaceName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Guild::Model::FNamespacePtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Guild::Model::FNamespace>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Guild::Model::FNamespace::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FNamespaceCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Guild::Model::FNamespacePtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            TimeOffset
        );
    }

    void FNamespaceCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Guild::Model::FNamespace::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentNamespaceName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Guild::Model::FNamespacePtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Guild::Model::FNamespacePtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Guild::Model::FNamespacePtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("namespace"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FNamespaceCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Guild::Model::FNamespacePtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Guild::Model::FNamespace::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Guild::Model::FNamespacePtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FNamespace>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FNamespaceCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Guild::Model::FNamespace::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}