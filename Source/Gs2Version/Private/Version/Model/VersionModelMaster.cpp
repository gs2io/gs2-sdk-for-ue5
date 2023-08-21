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

#include "Version/Model/VersionModelMaster.h"

namespace Gs2::Version::Model
{
    FVersionModelMaster::FVersionModelMaster():
        VersionModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        WarningVersionValue(nullptr),
        ErrorVersionValue(nullptr),
        ScopeValue(TOptional<FString>()),
        CurrentVersionValue(nullptr),
        NeedSignatureValue(TOptional<bool>()),
        SignatureKeyIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FVersionModelMaster::FVersionModelMaster(
        const FVersionModelMaster& From
    ):
        VersionModelIdValue(From.VersionModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        WarningVersionValue(From.WarningVersionValue),
        ErrorVersionValue(From.ErrorVersionValue),
        ScopeValue(From.ScopeValue),
        CurrentVersionValue(From.CurrentVersionValue),
        NeedSignatureValue(From.NeedSignatureValue),
        SignatureKeyIdValue(From.SignatureKeyIdValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithVersionModelId(
        const TOptional<FString> VersionModelId
    )
    {
        this->VersionModelIdValue = VersionModelId;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithWarningVersion(
        const TSharedPtr<FVersion> WarningVersion
    )
    {
        this->WarningVersionValue = WarningVersion;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithErrorVersion(
        const TSharedPtr<FVersion> ErrorVersion
    )
    {
        this->ErrorVersionValue = ErrorVersion;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithCurrentVersion(
        const TSharedPtr<FVersion> CurrentVersion
    )
    {
        this->CurrentVersionValue = CurrentVersion;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithNeedSignature(
        const TOptional<bool> NeedSignature
    )
    {
        this->NeedSignatureValue = NeedSignature;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithSignatureKeyId(
        const TOptional<FString> SignatureKeyId
    )
    {
        this->SignatureKeyIdValue = SignatureKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FVersionModelMaster::GetVersionModelId() const
    {
        return VersionModelIdValue;
    }
    TOptional<FString> FVersionModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FVersionModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FVersionModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<FVersion> FVersionModelMaster::GetWarningVersion() const
    {
        return WarningVersionValue;
    }
    TSharedPtr<FVersion> FVersionModelMaster::GetErrorVersion() const
    {
        return ErrorVersionValue;
    }
    TOptional<FString> FVersionModelMaster::GetScope() const
    {
        return ScopeValue;
    }
    TSharedPtr<FVersion> FVersionModelMaster::GetCurrentVersion() const
    {
        return CurrentVersionValue;
    }
    TOptional<bool> FVersionModelMaster::GetNeedSignature() const
    {
        return NeedSignatureValue;
    }

    FString FVersionModelMaster::GetNeedSignatureString() const
    {
        if (!NeedSignatureValue.IsSet())
        {
            return FString("null");
        }
        return FString(NeedSignatureValue.GetValue() ? "true" : "false");
    }
    TOptional<FString> FVersionModelMaster::GetSignatureKeyId() const
    {
        return SignatureKeyIdValue;
    }
    TOptional<int64> FVersionModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FVersionModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FVersionModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FVersionModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FVersionModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FVersionModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FVersionModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FVersionModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FVersionModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FVersionModelMaster::GetVersionNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):version:(?<namespaceName>.+):model:version:(?<versionName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FVersionModelMaster> FVersionModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FVersionModelMaster>()
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
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("description", v))
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
            ->WithScope(Data->HasField("scope") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("scope", v))
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
                }() : TOptional<FString>())
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

    TSharedPtr<FJsonObject> FVersionModelMaster::ToJson() const
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
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (WarningVersionValue != nullptr && WarningVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("warningVersion", WarningVersionValue->ToJson());
        }
        if (ErrorVersionValue != nullptr && ErrorVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("errorVersion", ErrorVersionValue->ToJson());
        }
        if (ScopeValue.IsSet())
        {
            JsonRootObject->SetStringField("scope", ScopeValue.GetValue());
        }
        if (CurrentVersionValue != nullptr && CurrentVersionValue.IsValid())
        {
            JsonRootObject->SetObjectField("currentVersion", CurrentVersionValue->ToJson());
        }
        if (NeedSignatureValue.IsSet())
        {
            JsonRootObject->SetBoolField("needSignature", NeedSignatureValue.GetValue());
        }
        if (SignatureKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("signatureKeyId", SignatureKeyIdValue.GetValue());
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

    FString FVersionModelMaster::TypeName = "VersionModelMaster";
}