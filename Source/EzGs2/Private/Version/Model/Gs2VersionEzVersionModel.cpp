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

#include "Version/Model/Gs2VersionEzVersionModel.h"

namespace Gs2::UE5::Version::Model
{

    TSharedPtr<FEzVersionModel> FEzVersionModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersionModel> FEzVersionModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersionModel> FEzVersionModel::WithWarningVersion(
        const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> WarningVersion
    )
    {
        this->WarningVersionValue = WarningVersion;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersionModel> FEzVersionModel::WithErrorVersion(
        const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> ErrorVersion
    )
    {
        this->ErrorVersionValue = ErrorVersion;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersionModel> FEzVersionModel::WithScope(
        const TOptional<FString> Scope
    )
    {
        this->ScopeValue = Scope;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersionModel> FEzVersionModel::WithCurrentVersion(
        const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> CurrentVersion
    )
    {
        this->CurrentVersionValue = CurrentVersion;
        return SharedThis(this);
    }

    TSharedPtr<FEzVersionModel> FEzVersionModel::WithNeedSignature(
        const TOptional<bool> NeedSignature
    )
    {
        this->NeedSignatureValue = NeedSignature;
        return SharedThis(this);
    }
    TOptional<FString> FEzVersionModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzVersionModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> FEzVersionModel::GetWarningVersion() const
    {
        return WarningVersionValue;
    }
    TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> FEzVersionModel::GetErrorVersion() const
    {
        return ErrorVersionValue;
    }
    TOptional<FString> FEzVersionModel::GetScope() const
    {
        return ScopeValue;
    }
    TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> FEzVersionModel::GetCurrentVersion() const
    {
        return CurrentVersionValue;
    }
    TOptional<bool> FEzVersionModel::GetNeedSignature() const
    {
        return NeedSignatureValue;
    }

    FString FEzVersionModel::GetNeedSignatureString() const
    {
        if (!NeedSignatureValue.IsSet())
        {
            return FString("null");
        }
        return FString(NeedSignatureValue.GetValue() ? "true" : "false");
    }

    Gs2::Version::Model::FVersionModelPtr FEzVersionModel::ToModel() const
    {
        return MakeShared<Gs2::Version::Model::FVersionModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithWarningVersion(WarningVersionValue == nullptr ? nullptr : WarningVersionValue->ToModel())
            ->WithErrorVersion(ErrorVersionValue == nullptr ? nullptr : ErrorVersionValue->ToModel())
            ->WithScope(ScopeValue)
            ->WithCurrentVersion(CurrentVersionValue == nullptr ? nullptr : CurrentVersionValue->ToModel())
            ->WithNeedSignature(NeedSignatureValue);
    }

    TSharedPtr<FEzVersionModel> FEzVersionModel::FromModel(const Gs2::Version::Model::FVersionModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzVersionModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithWarningVersion(Model->GetWarningVersion() != nullptr ? Gs2::UE5::Version::Model::FEzVersion::FromModel(Model->GetWarningVersion()) : nullptr)
            ->WithErrorVersion(Model->GetErrorVersion() != nullptr ? Gs2::UE5::Version::Model::FEzVersion::FromModel(Model->GetErrorVersion()) : nullptr)
            ->WithScope(Model->GetScope())
            ->WithCurrentVersion(Model->GetCurrentVersion() != nullptr ? Gs2::UE5::Version::Model::FEzVersion::FromModel(Model->GetCurrentVersion()) : nullptr)
            ->WithNeedSignature(Model->GetNeedSignature());
    }
}