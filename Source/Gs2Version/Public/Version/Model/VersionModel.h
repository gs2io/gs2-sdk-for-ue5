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
#include "Version.h"

namespace Gs2::Version::Model
{
    class GS2VERSION_API FVersionModel final : public TSharedFromThis<FVersionModel>
    {
        TOptional<FString> VersionModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<FVersion> WarningVersionValue;
        TSharedPtr<FVersion> ErrorVersionValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<FVersion> CurrentVersionValue;
        TOptional<bool> NeedSignatureValue;
        TOptional<FString> SignatureKeyIdValue;

    public:
        FVersionModel();
        FVersionModel(
            const FVersionModel& From
        );
        ~FVersionModel() = default;

        TSharedPtr<FVersionModel> WithVersionModelId(const TOptional<FString> VersionModelId);
        TSharedPtr<FVersionModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FVersionModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FVersionModel> WithWarningVersion(const TSharedPtr<FVersion> WarningVersion);
        TSharedPtr<FVersionModel> WithErrorVersion(const TSharedPtr<FVersion> ErrorVersion);
        TSharedPtr<FVersionModel> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FVersionModel> WithCurrentVersion(const TSharedPtr<FVersion> CurrentVersion);
        TSharedPtr<FVersionModel> WithNeedSignature(const TOptional<bool> NeedSignature);
        TSharedPtr<FVersionModel> WithSignatureKeyId(const TOptional<FString> SignatureKeyId);

        TOptional<FString> GetVersionModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<FVersion> GetWarningVersion() const;
        TSharedPtr<FVersion> GetErrorVersion() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<FVersion> GetCurrentVersion() const;
        TOptional<bool> GetNeedSignature() const;
        FString GetNeedSignatureString() const;
        TOptional<FString> GetSignatureKeyId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetVersionNameFromGrn(const FString Grn);

        static TSharedPtr<FVersionModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FVersionModel, ESPMode::ThreadSafe> FVersionModelPtr;
}