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

#include "StateMachine/Model/Namespace.h"

namespace Gs2::StateMachine::Model
{
    FNamespace::FNamespace():
        NamespaceIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        SupportSpeculativeExecutionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        StartScriptValue(nullptr),
        PassScriptValue(nullptr),
        ErrorScriptValue(nullptr),
        LowestStateMachineVersionValue(TOptional<int64>()),
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
        SupportSpeculativeExecutionValue(From.SupportSpeculativeExecutionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        StartScriptValue(From.StartScriptValue),
        PassScriptValue(From.PassScriptValue),
        ErrorScriptValue(From.ErrorScriptValue),
        LowestStateMachineVersionValue(From.LowestStateMachineVersionValue),
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

    TSharedPtr<FNamespace> FNamespace::WithSupportSpeculativeExecution(
        const TOptional<FString> SupportSpeculativeExecution
    )
    {
        this->SupportSpeculativeExecutionValue = SupportSpeculativeExecution;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithTransactionSetting(
        const TSharedPtr<FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithStartScript(
        const TSharedPtr<FScriptSetting> StartScript
    )
    {
        this->StartScriptValue = StartScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithPassScript(
        const TSharedPtr<FScriptSetting> PassScript
    )
    {
        this->PassScriptValue = PassScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithErrorScript(
        const TSharedPtr<FScriptSetting> ErrorScript
    )
    {
        this->ErrorScriptValue = ErrorScript;
        return SharedThis(this);
    }

    TSharedPtr<FNamespace> FNamespace::WithLowestStateMachineVersion(
        const TOptional<int64> LowestStateMachineVersion
    )
    {
        this->LowestStateMachineVersionValue = LowestStateMachineVersion;
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
    TOptional<FString> FNamespace::GetSupportSpeculativeExecution() const
    {
        return SupportSpeculativeExecutionValue;
    }
    TSharedPtr<FTransactionSetting> FNamespace::GetTransactionSetting() const
    {
        return TransactionSettingValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetStartScript() const
    {
        return StartScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetPassScript() const
    {
        return PassScriptValue;
    }
    TSharedPtr<FScriptSetting> FNamespace::GetErrorScript() const
    {
        return ErrorScriptValue;
    }
    TOptional<int64> FNamespace::GetLowestStateMachineVersion() const
    {
        return LowestStateMachineVersionValue;
    }

    FString FNamespace::GetLowestStateMachineVersionString() const
    {
        if (!LowestStateMachineVersionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), LowestStateMachineVersionValue.GetValue());
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
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FNamespace::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):stateMachine:(?<namespaceName>.+)"));
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
            ->WithSupportSpeculativeExecution(Data->HasField("supportSpeculativeExecution") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("supportSpeculativeExecution", v))
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
            ->WithStartScript(Data->HasField("startScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("startScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("startScript"));
                 }() : nullptr)
            ->WithPassScript(Data->HasField("passScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("passScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("passScript"));
                 }() : nullptr)
            ->WithErrorScript(Data->HasField("errorScript") ? [Data]() -> Model::FScriptSettingPtr
                {
                    if (Data->HasTypedField<EJson::Null>("errorScript"))
                    {
                        return nullptr;
                    }
                    return Model::FScriptSetting::FromJson(Data->GetObjectField("errorScript"));
                 }() : nullptr)
            ->WithLowestStateMachineVersion(Data->HasField("lowestStateMachineVersion") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("lowestStateMachineVersion", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
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
        if (SupportSpeculativeExecutionValue.IsSet())
        {
            JsonRootObject->SetStringField("supportSpeculativeExecution", SupportSpeculativeExecutionValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (StartScriptValue != nullptr && StartScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("startScript", StartScriptValue->ToJson());
        }
        if (PassScriptValue != nullptr && PassScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("passScript", PassScriptValue->ToJson());
        }
        if (ErrorScriptValue != nullptr && ErrorScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("errorScript", ErrorScriptValue->ToJson());
        }
        if (LowestStateMachineVersionValue.IsSet())
        {
            JsonRootObject->SetStringField("lowestStateMachineVersion", FString::Printf(TEXT("%lld"), LowestStateMachineVersionValue.GetValue()));
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