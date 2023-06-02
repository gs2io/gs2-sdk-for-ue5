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
#include "Core/Gs2Object.h"
#include "Version.h"

namespace Gs2::Version::Model
{
    class GS2VERSION_API FVersionModelMaster final : public Gs2Object, public TSharedFromThis<FVersionModelMaster>
    {
        TOptional<FString> VersionModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<FVersion> WarningVersionValue;
        TSharedPtr<FVersion> ErrorVersionValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<FVersion> CurrentVersionValue;
        TOptional<bool> NeedSignatureValue;
        TOptional<FString> SignatureKeyIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FVersionModelMaster();
        FVersionModelMaster(
            const FVersionModelMaster& From
        );
        virtual ~FVersionModelMaster() override = default;

        TSharedPtr<FVersionModelMaster> WithVersionModelId(const TOptional<FString> VersionModelId);
        TSharedPtr<FVersionModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FVersionModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FVersionModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FVersionModelMaster> WithWarningVersion(const TSharedPtr<FVersion> WarningVersion);
        TSharedPtr<FVersionModelMaster> WithErrorVersion(const TSharedPtr<FVersion> ErrorVersion);
        TSharedPtr<FVersionModelMaster> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FVersionModelMaster> WithCurrentVersion(const TSharedPtr<FVersion> CurrentVersion);
        TSharedPtr<FVersionModelMaster> WithNeedSignature(const TOptional<bool> NeedSignature);
        TSharedPtr<FVersionModelMaster> WithSignatureKeyId(const TOptional<FString> SignatureKeyId);
        TSharedPtr<FVersionModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FVersionModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetVersionModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<FVersion> GetWarningVersion() const;
        TSharedPtr<FVersion> GetErrorVersion() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<FVersion> GetCurrentVersion() const;
        TOptional<bool> GetNeedSignature() const;
        FString GetNeedSignatureString() const;
        TOptional<FString> GetSignatureKeyId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetVersionNameFromGrn(const FString Grn);

        static TSharedPtr<FVersionModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FVersionModelMaster, ESPMode::ThreadSafe> FVersionModelMasterPtr;
}