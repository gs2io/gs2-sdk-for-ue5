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

#include "Inventory/Model/Namespace.h"

namespace Gs2::Inventory::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        AcquireScriptValue(nullptr),
        OverflowScriptValue(nullptr),
        ConsumeScriptValue(nullptr),
        SimpleItemAcquireScriptValue(nullptr),
        SimpleItemConsumeScriptValue(nullptr),
        BigItemAcquireScriptValue(nullptr),
        BigItemConsumeScriptValue(nullptr),
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
        AcquireScriptValue(From.AcquireScriptValue),
        OverflowScriptValue(From.OverflowScriptValue),
        ConsumeScriptValue(From.ConsumeScriptValue),
        SimpleItemAcquireScriptValue(From.SimpleItemAcquireScriptValue),
        SimpleItemConsumeScriptValue(From.SimpleItemConsumeScriptValue),
        BigItemAcquireScriptValue(From.BigItemAcquireScriptValue),
        BigItemConsumeScriptValue(From.BigItemConsumeScriptValue),
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

    TSharedPtr<FNamespace> FNamespace::WithAcquireScript(
        const TSharedPtr<FScriptSetting> AcquireScript
    )
    {
        this->AcquireScriptValue = AcquireScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithOverflowScript(
        const TSharedPtr<FScriptSetting> OverflowScript
    )
    {
        this->OverflowScriptValue = OverflowScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithConsumeScript(
        const TSharedPtr<FScriptSetting> ConsumeScript
    )
    {
        this->ConsumeScriptValue = ConsumeScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithSimpleItemAcquireScript(
        const TSharedPtr<FScriptSetting> SimpleItemAcquireScript
    )
    {
        this->SimpleItemAcquireScriptValue = SimpleItemAcquireScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithSimpleItemConsumeScript(
        const TSharedPtr<FScriptSetting> SimpleItemConsumeScript
    )
    {
        this->SimpleItemConsumeScriptValue = SimpleItemConsumeScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithBigItemAcquireScript(
        const TSharedPtr<FScriptSetting> BigItemAcquireScript
    )
    {
        this->BigItemAcquireScriptValue = BigItemAcquireScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithBigItemConsumeScript(
        const TSharedPtr<FScriptSetting> BigItemConsumeScript
    )
    {
        this->BigItemConsumeScriptValue = BigItemConsumeScript;
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
    TSharedPtr<FScriptSetting> FNamespace::GetAcquireScript() const
    {
        return AcquireScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetOverflowScript() const
    {
        return OverflowScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetConsumeScript() const
    {
        return ConsumeScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetSimpleItemAcquireScript() const
    {
        return SimpleItemAcquireScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetSimpleItemConsumeScript() const
    {
        return SimpleItemConsumeScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetBigItemAcquireScript() const
    {
        return BigItemAcquireScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetBigItemConsumeScript() const
    {
        return BigItemConsumeScriptValue;
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+)"));
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
            ->WithAcquireScript(Data->HasField(ANSI_TO_TCHAR("acquireScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("acquireScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("acquireScript")));
                 }() : nullptr)
            ->WithOverflowScript(Data->HasField(ANSI_TO_TCHAR("overflowScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("overflowScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("overflowScript")));
                 }() : nullptr)
            ->WithConsumeScript(Data->HasField(ANSI_TO_TCHAR("consumeScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("consumeScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("consumeScript")));
                 }() : nullptr)
            ->WithSimpleItemAcquireScript(Data->HasField(ANSI_TO_TCHAR("simpleItemAcquireScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("simpleItemAcquireScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("simpleItemAcquireScript")));
                 }() : nullptr)
            ->WithSimpleItemConsumeScript(Data->HasField(ANSI_TO_TCHAR("simpleItemConsumeScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("simpleItemConsumeScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("simpleItemConsumeScript")));
                 }() : nullptr)
            ->WithBigItemAcquireScript(Data->HasField(ANSI_TO_TCHAR("bigItemAcquireScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("bigItemAcquireScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("bigItemAcquireScript")));
                 }() : nullptr)
            ->WithBigItemConsumeScript(Data->HasField(ANSI_TO_TCHAR("bigItemConsumeScript")) ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("bigItemConsumeScript")))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("bigItemConsumeScript")));
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
        if (AcquireScriptValue != nullptr && AcquireScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("acquireScript", AcquireScriptValue->ToJson());
        }
        if (OverflowScriptValue != nullptr && OverflowScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("overflowScript", OverflowScriptValue->ToJson());
        }
        if (ConsumeScriptValue != nullptr && ConsumeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("consumeScript", ConsumeScriptValue->ToJson());
        }
        if (SimpleItemAcquireScriptValue != nullptr && SimpleItemAcquireScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("simpleItemAcquireScript", SimpleItemAcquireScriptValue->ToJson());
        }
        if (SimpleItemConsumeScriptValue != nullptr && SimpleItemConsumeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("simpleItemConsumeScript", SimpleItemConsumeScriptValue->ToJson());
        }
        if (BigItemAcquireScriptValue != nullptr && BigItemAcquireScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("bigItemAcquireScript", BigItemAcquireScriptValue->ToJson());
        }
        if (BigItemConsumeScriptValue != nullptr && BigItemConsumeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("bigItemConsumeScript", BigItemConsumeScriptValue->ToJson());
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