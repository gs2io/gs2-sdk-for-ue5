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

#include "Quest/Model/Namespace.h"

namespace Gs2::Quest::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        StartQuestScriptValue(nullptr),
        CompleteQuestScriptValue(nullptr),
        FailedQuestScriptValue(nullptr),
        LogSettingValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        QueueNamespaceIdValue(TOptional<FString>()),
        KeyIdValue(TOptional<FString>())
    {
    }

    FNamespace::FNamespace(
        const FNamespace& From
    ):
        NamespaceIdValue(From.NamespaceIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        StartQuestScriptValue(From.StartQuestScriptValue),
        CompleteQuestScriptValue(From.CompleteQuestScriptValue),
        FailedQuestScriptValue(From.FailedQuestScriptValue),
        LogSettingValue(From.LogSettingValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        QueueNamespaceIdValue(From.QueueNamespaceIdValue),
        KeyIdValue(From.KeyIdValue)
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

    TSharedPtr<FNamespace> FNamespace::WithStartQuestScript(
        const TSharedPtr<FScriptSetting> StartQuestScript
    )
    {
        this->StartQuestScriptValue = StartQuestScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithCompleteQuestScript(
        const TSharedPtr<FScriptSetting> CompleteQuestScript
    )
    {
        this->CompleteQuestScriptValue = CompleteQuestScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithFailedQuestScript(
        const TSharedPtr<FScriptSetting> FailedQuestScript
    )
    {
        this->FailedQuestScriptValue = FailedQuestScript;
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

    TSharedPtr<FNamespace> FNamespace::WithQueueNamespaceId(
        const TOptional<FString> QueueNamespaceId
    )
    {
        this->QueueNamespaceIdValue = QueueNamespaceId;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithKeyId(
        const TOptional<FString> KeyId
    )
    {
        this->KeyIdValue = KeyId;
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
    TSharedPtr<FScriptSetting> FNamespace::GetStartQuestScript() const
    {
        return StartQuestScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetCompleteQuestScript() const
    {
        return CompleteQuestScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetFailedQuestScript() const
    {
        return FailedQuestScriptValue;
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
    TOptional<FString> FNamespace::GetQueueNamespaceId() const
    {
        return QueueNamespaceIdValue;
    }
    TOptional<FString> FNamespace::GetKeyId() const
    {
        return KeyIdValue;
    }

    TOptional<FString> FNamespace::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):quest:(?<namespaceName>.+)"));
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
            ->WithTransactionSetting(Data->HasField("transactionSetting") ? [Data]() -> Model::FTransactionSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("transactionSetting"))
                    {
                        return nullptr;
                    }
                    return Model::FTransactionSetting::FromJson(Data->GetObjectField("transactionSetting"));
                 }() : nullptr)
            ->WithStartQuestScript(Data->HasField("startQuestScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("startQuestScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("startQuestScript"));
                 }() : nullptr)
            ->WithCompleteQuestScript(Data->HasField("completeQuestScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("completeQuestScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("completeQuestScript"));
                 }() : nullptr)
            ->WithFailedQuestScript(Data->HasField("failedQuestScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("failedQuestScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("failedQuestScript"));
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
            ->WithQueueNamespaceId(Data->HasField("queueNamespaceId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("queueNamespaceId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithKeyId(Data->HasField("keyId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("keyId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
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
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (StartQuestScriptValue != nullptr && StartQuestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("startQuestScript", StartQuestScriptValue->ToJson());
        }
        if (CompleteQuestScriptValue != nullptr && CompleteQuestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("completeQuestScript", CompleteQuestScriptValue->ToJson());
        }
        if (FailedQuestScriptValue != nullptr && FailedQuestScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("failedQuestScript", FailedQuestScriptValue->ToJson());
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
        if (QueueNamespaceIdValue.IsSet())
        {
            JsonRootObject->SetStringField("queueNamespaceId", QueueNamespaceIdValue.GetValue());
        }
        if (KeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("keyId", KeyIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FNamespace::TypeName = "Namespace";
}