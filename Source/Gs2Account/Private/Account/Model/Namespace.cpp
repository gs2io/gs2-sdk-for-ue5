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

#include "Account/Model/Namespace.h"

namespace Gs2::Account::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        ChangePasswordIfTakeOverValue(TOptional<bool>()),
        DifferentUserIdForLoginAndDataRetentionValue(TOptional<bool>()),
        CreateAccountScriptValue(nullptr),
        AuthenticationScriptValue(nullptr),
        CreateTakeOverScriptValue(nullptr),
        DoTakeOverScriptValue(nullptr),
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
        ChangePasswordIfTakeOverValue(From.ChangePasswordIfTakeOverValue),
        DifferentUserIdForLoginAndDataRetentionValue(From.DifferentUserIdForLoginAndDataRetentionValue),
        CreateAccountScriptValue(From.CreateAccountScriptValue),
        AuthenticationScriptValue(From.AuthenticationScriptValue),
        CreateTakeOverScriptValue(From.CreateTakeOverScriptValue),
        DoTakeOverScriptValue(From.DoTakeOverScriptValue),
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

    TSharedPtr<FNamespace> FNamespace::WithChangePasswordIfTakeOver(
        const TOptional<bool> ChangePasswordIfTakeOver
    )
    {
        this->ChangePasswordIfTakeOverValue = ChangePasswordIfTakeOver;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDifferentUserIdForLoginAndDataRetention(
        const TOptional<bool> DifferentUserIdForLoginAndDataRetention
    )
    {
        this->DifferentUserIdForLoginAndDataRetentionValue = DifferentUserIdForLoginAndDataRetention;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateAccountScript(
        const TSharedPtr<FScriptSetting> CreateAccountScript
    )
    {
        this->CreateAccountScriptValue = CreateAccountScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithAuthenticationScript(
        const TSharedPtr<FScriptSetting> AuthenticationScript
    )
    {
        this->AuthenticationScriptValue = AuthenticationScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCreateTakeOverScript(
        const TSharedPtr<FScriptSetting> CreateTakeOverScript
    )
    {
        this->CreateTakeOverScriptValue = CreateTakeOverScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithDoTakeOverScript(
        const TSharedPtr<FScriptSetting> DoTakeOverScript
    )
    {
        this->DoTakeOverScriptValue = DoTakeOverScript;
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
    TOptional<bool> FNamespace::GetChangePasswordIfTakeOver() const
    {
        return ChangePasswordIfTakeOverValue;
    }

    FString FNamespace::GetChangePasswordIfTakeOverString() const
    {
        if (!ChangePasswordIfTakeOverValue.IsSet())
        {
            return FString("null");
        }
        return FString(ChangePasswordIfTakeOverValue.GetValue() ? "true" : "false");
    }
    TOptional<bool> FNamespace::GetDifferentUserIdForLoginAndDataRetention() const
    {
        return DifferentUserIdForLoginAndDataRetentionValue;
    }

    FString FNamespace::GetDifferentUserIdForLoginAndDataRetentionString() const
    {
        if (!DifferentUserIdForLoginAndDataRetentionValue.IsSet())
        {
            return FString("null");
        }
        return FString(DifferentUserIdForLoginAndDataRetentionValue.GetValue() ? "true" : "false");
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCreateAccountScript() const
    {
        return CreateAccountScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetAuthenticationScript() const
    {
        return AuthenticationScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCreateTakeOverScript() const
    {
        return CreateTakeOverScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetDoTakeOverScript() const
    {
        return DoTakeOverScriptValue;
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):account:(?<namespaceName>.+)"));
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
                    FString v;
                    if (Data->TryGetStringField("namespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
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
            ->WithChangePasswordIfTakeOver(Data->HasField("changePasswordIfTakeOver") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("changePasswordIfTakeOver", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithDifferentUserIdForLoginAndDataRetention(Data->HasField("differentUserIdForLoginAndDataRetention") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("differentUserIdForLoginAndDataRetention", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithCreateAccountScript(Data->HasField("createAccountScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("createAccountScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("createAccountScript"));
                 }() : nullptr)
            ->WithAuthenticationScript(Data->HasField("authenticationScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("authenticationScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("authenticationScript"));
                 }() : nullptr)
            ->WithCreateTakeOverScript(Data->HasField("createTakeOverScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("createTakeOverScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("createTakeOverScript"));
                 }() : nullptr)
            ->WithDoTakeOverScript(Data->HasField("doTakeOverScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("doTakeOverScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("doTakeOverScript"));
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
        if (ChangePasswordIfTakeOverValue.IsSet())
        {
            JsonRootObject->SetBoolField("changePasswordIfTakeOver", ChangePasswordIfTakeOverValue.GetValue());
        }
        if (DifferentUserIdForLoginAndDataRetentionValue.IsSet())
        {
            JsonRootObject->SetBoolField("differentUserIdForLoginAndDataRetention", DifferentUserIdForLoginAndDataRetentionValue.GetValue());
        }
        if (CreateAccountScriptValue != nullptr && CreateAccountScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createAccountScript", CreateAccountScriptValue->ToJson());
        }
        if (AuthenticationScriptValue != nullptr && AuthenticationScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("authenticationScript", AuthenticationScriptValue->ToJson());
        }
        if (CreateTakeOverScriptValue != nullptr && CreateTakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("createTakeOverScript", CreateTakeOverScriptValue->ToJson());
        }
        if (DoTakeOverScriptValue != nullptr && DoTakeOverScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("doTakeOverScript", DoTakeOverScriptValue->ToJson());
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