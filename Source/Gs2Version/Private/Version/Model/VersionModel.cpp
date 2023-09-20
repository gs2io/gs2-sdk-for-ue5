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

#include "Version/Model/VersionModel.h"

namespace Gs2::Version::Model
{
    FVersionModel::FVersionModel():
        VersionModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ScopeValue(TOptional<FString>()),
        TypeValue(TOptional<FString>()),
        CurrentVersionValue(nullptr),
        WarningVersionValue(nullptr),
        ErrorVersionValue(nullptr),
        ScheduleVersionsValue(nullptr),
        NeedSignatureValue(TOptional<bool>()),
        SignatureKeyIdValue(TOptional<FString>())
    {
    }

    FVersionModel::FVersionModel(
        const FVersionModel& From
    ):
        VersionModelIdValue(From.VersionModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        ScopeValue(From.ScopeValue),
        TypeValue(From.TypeValue),
        CurrentVersionValue(From.CurrentVersionValue),
        WarningVersionValue(From.WarningVersionValue),
        ErrorVersionValue(From.ErrorVersionValue),
        ScheduleVersionsValue(From.ScheduleVersionsValue),
        NeedSignatureValue(From.NeedSignatureValue),
        SignatureKeyIdValue(From.SignatureKeyIdValue)
    {
    }

    TSharedPtr<FVersionModel> FVersionModel::WithVersionModelId(
        const TOptional<FString> VersionModelId
    )
    {
        this->VersionModelIdValue = VersionModelId;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithCurrentVersion(
        const TSharedPtr<FVersion> CurrentVersion
    )
    {
        this->CurrentVersionValue = CurrentVersion;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithWarningVersion(
        const TSharedPtr<FVersion> WarningVersion
    )
    {
        this->WarningVersionValue = WarningVersion;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithErrorVersion(
        const TSharedPtr<FVersion> ErrorVersion
    )
    {
        this->ErrorVersionValue = ErrorVersion;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithScheduleVersions(
        const TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> ScheduleVersions
    )
    {
        this->ScheduleVersionsValue = ScheduleVersions;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithNeedSignature(
        const TOptional<bool> NeedSignature
    )
    {
        this->NeedSignatureValue = NeedSignature;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModel> FVersionModel::WithSignatureKeyId(
        const TOptional<FString> SignatureKeyId
    )
    {
        this->SignatureKeyIdValue = SignatureKeyId;
        return SharedThis(this);
    }
    TOptional<FString> FVersionModel::GetVersionModelId() const
    {
        return VersionModelIdValue;
    }
    TOptional<FString> FVersionModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FVersionModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FVersionModel::GetScope() const
    {
        return ScopeValue;
    }
    TOptional<FString> FVersionModel::GetType() const
    {
        return TypeValue;
    }
    TSharedPtr<FVersion> FVersionModel::GetCurrentVersion() const
    {
        return CurrentVersionValue;
    }
    TSharedPtr<FVersion> FVersionModel::GetWarningVersion() const
    {
        return WarningVersionValue;
    }
    TSharedPtr<FVersion> FVersionModel::GetErrorVersion() const
    {
        return ErrorVersionValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> FVersionModel::GetScheduleVersions() const
    {
        return ScheduleVersionsValue;
    }
    TOptional<bool> FVersionModel::GetNeedSignature() const
    {
        return NeedSignatureValue;
    }

    FString FVersionModel::GetNeedSignatureString() const
    {
        if (!NeedSignatureValue.IsSet())
        {
            return FString("null");
        }
        return FString(NeedSignatureValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FVersionModel::GetSignatureKeyId() const
    {
        return SignatureKeyIdValue;
    }

    TOptional<FString> FVersionModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FVersionModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FVersionModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FVersionModel::GetVersionNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FVersionModel> FVersionModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVersionModel>()
            ->WithVersionModelId(Data->HasField("versionModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("versionModelId", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithScope(Data->HasField("scope") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scope", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithType(Data->HasField("type") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("type", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCurrentVersion(Data->HasField("currentVersion") ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("currentVersion"))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField("currentVersion"));
                 }() : nullptr)
            ->WithWarningVersion(Data->HasField("warningVersion") ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("warningVersion"))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField("warningVersion"));
                 }() : nullptr)
            ->WithErrorVersion(Data->HasField("errorVersion") ? [Data]() -> Model::FVersionPtr
                {
                    if (Data->HasTypedField<EJson::Null>("errorVersion"))
                    {
                        return nullptr;
                    }
                    return Model::FVersion::FromJson(Data->GetObjectField("errorVersion"));
                 }() : nullptr)
            ->WithScheduleVersions(Data->HasField("scheduleVersions") ? [Data]() -> TSharedPtr<TArray<Model::FScheduleVersionPtr>>
                {
                    auto v = MakeShared<TArray<Model::FScheduleVersionPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("scheduleVersions") && Data->HasTypedField<EJson::Array>("scheduleVersions"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("scheduleVersions"))
                        {
                            v->Add(Model::FScheduleVersion::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FScheduleVersionPtr>>())
            ->WithNeedSignature(Data->HasField("needSignature") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("needSignature", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithSignatureKeyId(Data->HasField("signatureKeyId") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("signatureKeyId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FVersionModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (VersionModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("versionModelId", VersionModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField("scope", ScopeValue.GetValue());
        }
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (CurrentVersionValue != nullptr && CurrentVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("currentVersion", CurrentVersionValue->ToJson());
        }
        if (WarningVersionValue != nullptr && WarningVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("warningVersion", WarningVersionValue->ToJson());
        }
        if (ErrorVersionValue != nullptr && ErrorVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("errorVersion", ErrorVersionValue->ToJson());
        }
        if (ScheduleVersionsValue != nullptr && ScheduleVersionsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ScheduleVersionsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("scheduleVersions", v);
        }
        if (NeedSignatureValue.IsSet())
        {
            JsonRootObject->SetBoolField("needSignature", NeedSignatureValue.GetValue());
        }
        if (SignatureKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("signatureKeyId", SignatureKeyIdValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FVersionModel::TypeName = "VersionModel";
}