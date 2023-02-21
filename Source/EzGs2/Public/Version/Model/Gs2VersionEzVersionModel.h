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

#pragma once

#include "CoreMinimal.h"
#include "Version/Model/VersionModel.h"
#include "Gs2VersionEzVersion.h"
#include "Gs2VersionEzVersion.h"
#include "Gs2VersionEzVersion.h"

namespace Gs2::UE5::Version::Model
{
	class EZGS2_API FEzVersionModel final : public TSharedFromThis<FEzVersionModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> WarningVersionValue;
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> ErrorVersionValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> CurrentVersionValue;
        TOptional<bool> NeedSignatureValue;

	public:
        TSharedPtr<FEzVersionModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzVersionModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzVersionModel> WithWarningVersion(const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> WarningVersion);
        TSharedPtr<FEzVersionModel> WithErrorVersion(const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> ErrorVersion);
        TSharedPtr<FEzVersionModel> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FEzVersionModel> WithCurrentVersion(const TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> CurrentVersion);
        TSharedPtr<FEzVersionModel> WithNeedSignature(const TOptional<bool> NeedSignature);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> GetWarningVersion() const;

        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> GetErrorVersion() const;

        TOptional<FString> GetScope() const;

        TSharedPtr<Gs2::UE5::Version::Model::FEzVersion> GetCurrentVersion() const;

        TOptional<bool> GetNeedSignature() const;
        FString GetNeedSignatureString() const;

        Gs2::Version::Model::FVersionModelPtr ToModel() const;
        static TSharedPtr<FEzVersionModel> FromModel(Gs2::Version::Model::FVersionModelPtr Model);
    };
    typedef TSharedPtr<FEzVersionModel> FEzVersionModelPtr;
}