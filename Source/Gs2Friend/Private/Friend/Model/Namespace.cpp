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

#include "Friend/Model/Namespace.h"

namespace Gs2::Friend::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        FollowScriptValue(nullptr),
        UnfollowScriptValue(nullptr),
        SendRequestScriptValue(nullptr),
        CancelRequestScriptValue(nullptr),
        AcceptRequestScriptValue(nullptr),
        RejectRequestScriptValue(nullptr),
        DeleteFriendScriptValue(nullptr),
        UpdateProfileScriptValue(nullptr),
        FollowNotificationValue(nullptr),
        ReceiveRequestNotificationValue(nullptr),
        AcceptRequestNotificationValue(nullptr),
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
        FollowScriptValue(From.FollowScriptValue),
        UnfollowScriptValue(From.UnfollowScriptValue),
        SendRequestScriptValue(From.SendRequestScriptValue),
        CancelRequestScriptValue(From.CancelRequestScriptValue),
        AcceptRequestScriptValue(From.AcceptRequestScriptValue),
        RejectRequestScriptValue(From.RejectRequestScriptValue),
        DeleteFriendScriptValue(From.DeleteFriendScriptValue),
        UpdateProfileScriptValue(From.UpdateProfileScriptValue),
        FollowNotificationValue(From.FollowNotificationValue),
        ReceiveRequestNotificationValue(From.ReceiveRequestNotificationValue),
        AcceptRequestNotificationValue(From.AcceptRequestNotificationValue),
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

    TSharedPtr<FNamespace> FNamespace::WithFollowScript(
        const TSharedPtr<FScriptSetting> FollowScript
    )
    {
        this->FollowScriptValue = FollowScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUnfollowScript(
        const TSharedPtr<FScriptSetting> UnfollowScript
    )
    {
        this->UnfollowScriptValue = UnfollowScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithSendRequestScript(
        const TSharedPtr<FScriptSetting> SendRequestScript
    )
    {
        this->SendRequestScriptValue = SendRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCancelRequestScript(
        const TSharedPtr<FScriptSetting> CancelRequestScript
    )
    {
        this->CancelRequestScriptValue = CancelRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAcceptRequestScript(
        const TSharedPtr<FScriptSetting> AcceptRequestScript
    )
    {
        this->AcceptRequestScriptValue = AcceptRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithRejectRequestScript(
        const TSharedPtr<FScriptSetting> RejectRequestScript
    )
    {
        this->RejectRequestScriptValue = RejectRequestScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDeleteFriendScript(
        const TSharedPtr<FScriptSetting> DeleteFriendScript
    )
    {
        this->DeleteFriendScriptValue = DeleteFriendScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUpdateProfileScript(
        const TSharedPtr<FScriptSetting> UpdateProfileScript
    )
    {
        this->UpdateProfileScriptValue = UpdateProfileScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithFollowNotification(
        const TSharedPtr<FNotificationSetting> FollowNotification
    )
    {
        this->FollowNotificationValue = FollowNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithReceiveRequestNotification(
        const TSharedPtr<FNotificationSetting> ReceiveRequestNotification
    )
    {
        this->ReceiveRequestNotificationValue = ReceiveRequestNotification;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAcceptRequestNotification(
        const TSharedPtr<FNotificationSetting> AcceptRequestNotification
    )
    {
        this->AcceptRequestNotificationValue = AcceptRequestNotification;
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
    TSharedPtr<FScriptSetting> FNamespace::GetFollowScript() const
    {
        return FollowScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetUnfollowScript() const
    {
        return UnfollowScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetSendRequestScript() const
    {
        return SendRequestScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCancelRequestScript() const
    {
        return CancelRequestScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetAcceptRequestScript() const
    {
        return AcceptRequestScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetRejectRequestScript() const
    {
        return RejectRequestScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetDeleteFriendScript() const
    {
        return DeleteFriendScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetUpdateProfileScript() const
    {
        return UpdateProfileScriptValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetFollowNotification() const
    {
        return FollowNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetReceiveRequestNotification() const
    {
        return ReceiveRequestNotificationValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetAcceptRequestNotification() const
    {
        return AcceptRequestNotificationValue;
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):friend:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):friend:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):friend:(?<namespaceName>.+)"));
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
            ->WithFollowScript(Data->HasField(ANSI_TO_TCHAR("followScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("followScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("followScript")));
                 }() : nullptr)
            ->WithUnfollowScript(Data->HasField(ANSI_TO_TCHAR("unfollowScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("unfollowScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("unfollowScript")));
                 }() : nullptr)
            ->WithSendRequestScript(Data->HasField(ANSI_TO_TCHAR("sendRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("sendRequestScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("sendRequestScript")));
                 }() : nullptr)
            ->WithCancelRequestScript(Data->HasField(ANSI_TO_TCHAR("cancelRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("cancelRequestScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("cancelRequestScript")));
                 }() : nullptr)
            ->WithAcceptRequestScript(Data->HasField(ANSI_TO_TCHAR("acceptRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acceptRequestScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acceptRequestScript")));
                 }() : nullptr)
            ->WithRejectRequestScript(Data->HasField(ANSI_TO_TCHAR("rejectRequestScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("rejectRequestScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("rejectRequestScript")));
                 }() : nullptr)
            ->WithDeleteFriendScript(Data->HasField(ANSI_TO_TCHAR("deleteFriendScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("deleteFriendScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("deleteFriendScript")));
                 }() : nullptr)
            ->WithUpdateProfileScript(Data->HasField(ANSI_TO_TCHAR("updateProfileScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("updateProfileScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("updateProfileScript")));
                 }() : nullptr)
            ->WithFollowNotification(Data->HasField(ANSI_TO_TCHAR("followNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("followNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("followNotification")));
                 }() : nullptr)
            ->WithReceiveRequestNotification(Data->HasField(ANSI_TO_TCHAR("receiveRequestNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("receiveRequestNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("receiveRequestNotification")));
                 }() : nullptr)
            ->WithAcceptRequestNotification(Data->HasField(ANSI_TO_TCHAR("acceptRequestNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acceptRequestNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acceptRequestNotification")));
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
        if (FollowScriptValue != nullptr && FollowScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("followScript", FollowScriptValue->ToJson());
        }
        if (UnfollowScriptValue != nullptr && UnfollowScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("unfollowScript", UnfollowScriptValue->ToJson());
        }
        if (SendRequestScriptValue != nullptr && SendRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("sendRequestScript", SendRequestScriptValue->ToJson());
        }
        if (CancelRequestScriptValue != nullptr && CancelRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("cancelRequestScript", CancelRequestScriptValue->ToJson());
        }
        if (AcceptRequestScriptValue != nullptr && AcceptRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("acceptRequestScript", AcceptRequestScriptValue->ToJson());
        }
        if (RejectRequestScriptValue != nullptr && RejectRequestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("rejectRequestScript", RejectRequestScriptValue->ToJson());
        }
        if (DeleteFriendScriptValue != nullptr && DeleteFriendScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("deleteFriendScript", DeleteFriendScriptValue->ToJson());
        }
        if (UpdateProfileScriptValue != nullptr && UpdateProfileScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("updateProfileScript", UpdateProfileScriptValue->ToJson());
        }
        if (FollowNotificationValue != nullptr && FollowNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("followNotification", FollowNotificationValue->ToJson());
        }
        if (ReceiveRequestNotificationValue != nullptr && ReceiveRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("receiveRequestNotification", ReceiveRequestNotificationValue->ToJson());
        }
        if (AcceptRequestNotificationValue != nullptr && AcceptRequestNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("acceptRequestNotification", AcceptRequestNotificationValue->ToJson());
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