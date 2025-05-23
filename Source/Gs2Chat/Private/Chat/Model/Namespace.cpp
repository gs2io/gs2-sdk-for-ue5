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

#include "Chat/Model/Namespace.h"

namespace Gs2::Chat::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        AllowCreateRoomValue(TOptional<bool>()),
        MessageLifeTimeDaysValue(TOptional<int32>()),
        PostMessageScriptValue(nullptr),
        CreateRoomScriptValue(nullptr),
        DeleteRoomScriptValue(nullptr),
        SubscribeRoomScriptValue(nullptr),
        UnsubscribeRoomScriptValue(nullptr),
        PostNotificationValue(nullptr),
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
        AllowCreateRoomValue(From.AllowCreateRoomValue),
        MessageLifeTimeDaysValue(From.MessageLifeTimeDaysValue),
        PostMessageScriptValue(From.PostMessageScriptValue),
        CreateRoomScriptValue(From.CreateRoomScriptValue),
        DeleteRoomScriptValue(From.DeleteRoomScriptValue),
        SubscribeRoomScriptValue(From.SubscribeRoomScriptValue),
        UnsubscribeRoomScriptValue(From.UnsubscribeRoomScriptValue),
        PostNotificationValue(From.PostNotificationValue),
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

    TSharedPtr<FNamespace> FNamespace::WithAllowCreateRoom(
        const TOptional<bool> AllowCreateRoom
    )
    {
        this->AllowCreateRoomValue = AllowCreateRoom;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithMessageLifeTimeDays(
        const TOptional<int32> MessageLifeTimeDays
    )
    {
        this->MessageLifeTimeDaysValue = MessageLifeTimeDays;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithPostMessageScript(
        const TSharedPtr<FScriptSetting> PostMessageScript
    )
    {
        this->PostMessageScriptValue = PostMessageScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateRoomScript(
        const TSharedPtr<FScriptSetting> CreateRoomScript
    )
    {
        this->CreateRoomScriptValue = CreateRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDeleteRoomScript(
        const TSharedPtr<FScriptSetting> DeleteRoomScript
    )
    {
        this->DeleteRoomScriptValue = DeleteRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithSubscribeRoomScript(
        const TSharedPtr<FScriptSetting> SubscribeRoomScript
    )
    {
        this->SubscribeRoomScriptValue = SubscribeRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithUnsubscribeRoomScript(
        const TSharedPtr<FScriptSetting> UnsubscribeRoomScript
    )
    {
        this->UnsubscribeRoomScriptValue = UnsubscribeRoomScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithPostNotification(
        const TSharedPtr<FNotificationSetting> PostNotification
    )
    {
        this->PostNotificationValue = PostNotification;
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
    TOptional<bool> FNamespace::GetAllowCreateRoom() const
    {
        return AllowCreateRoomValue;
    }

    FString FNamespace::GetAllowCreateRoomString() const
    {
        if (!AllowCreateRoomValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowCreateRoomValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FNamespace::GetMessageLifeTimeDays() const
    {
        return MessageLifeTimeDaysValue;
    }

    FString FNamespace::GetMessageLifeTimeDaysString() const
    {
        if (!MessageLifeTimeDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MessageLifeTimeDaysValue.GetValue());
    }
    TSharedPtr<FScriptSetting> FNamespace::GetPostMessageScript() const
    {
        return PostMessageScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCreateRoomScript() const
    {
        return CreateRoomScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetDeleteRoomScript() const
    {
        return DeleteRoomScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetSubscribeRoomScript() const
    {
        return SubscribeRoomScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetUnsubscribeRoomScript() const
    {
        return UnsubscribeRoomScriptValue;
    }
    TSharedPtr<FNotificationSetting> FNamespace::GetPostNotification() const
    {
        return PostNotificationValue;
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):chat:(?<namespaceName>.+)"));
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
            ->WithAllowCreateRoom(Data->HasField(ANSI_TO_TCHAR("allowCreateRoom")) ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField(ANSI_TO_TCHAR("allowCreateRoom"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithMessageLifeTimeDays(Data->HasField(ANSI_TO_TCHAR("messageLifeTimeDays")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("messageLifeTimeDays"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithPostMessageScript(Data->HasField(ANSI_TO_TCHAR("postMessageScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("postMessageScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("postMessageScript")));
                 }() : nullptr)
            ->WithCreateRoomScript(Data->HasField(ANSI_TO_TCHAR("createRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("createRoomScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("createRoomScript")));
                 }() : nullptr)
            ->WithDeleteRoomScript(Data->HasField(ANSI_TO_TCHAR("deleteRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("deleteRoomScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("deleteRoomScript")));
                 }() : nullptr)
            ->WithSubscribeRoomScript(Data->HasField(ANSI_TO_TCHAR("subscribeRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("subscribeRoomScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("subscribeRoomScript")));
                 }() : nullptr)
            ->WithUnsubscribeRoomScript(Data->HasField(ANSI_TO_TCHAR("unsubscribeRoomScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("unsubscribeRoomScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("unsubscribeRoomScript")));
                 }() : nullptr)
            ->WithPostNotification(Data->HasField(ANSI_TO_TCHAR("postNotification")) ? [Data]() -> Model::FNotificationSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("postNotification")))
                    {
                        return nullptr;
                    }
                    return Model::FNotificationSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("postNotification")));
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
        if (AllowCreateRoomValue.IsSet())
        {
            JsonRootObject->SetBoolField("allowCreateRoom", AllowCreateRoomValue.GetValue());
        }
        if (MessageLifeTimeDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("messageLifeTimeDays", MessageLifeTimeDaysValue.GetValue());
        }
        if (PostMessageScriptValue != nullptr && PostMessageScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("postMessageScript", PostMessageScriptValue->ToJson());
        }
        if (CreateRoomScriptValue != nullptr && CreateRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createRoomScript", CreateRoomScriptValue->ToJson());
        }
        if (DeleteRoomScriptValue != nullptr && DeleteRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("deleteRoomScript", DeleteRoomScriptValue->ToJson());
        }
        if (SubscribeRoomScriptValue != nullptr && SubscribeRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("subscribeRoomScript", SubscribeRoomScriptValue->ToJson());
        }
        if (UnsubscribeRoomScriptValue != nullptr && UnsubscribeRoomScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("unsubscribeRoomScript", UnsubscribeRoomScriptValue->ToJson());
        }
        if (PostNotificationValue != nullptr && PostNotificationValue.IsValid())
        {
            JsonRootObject->SetObjectField("postNotification", PostNotificationValue->ToJson());
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