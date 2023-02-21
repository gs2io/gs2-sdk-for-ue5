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
#include "../Model/Version.h"

namespace Gs2::Version::Request
{
    class FUpdateVersionModelMasterRequest;

    class GS2VERSION_API FUpdateVersionModelMasterRequest final : public TSharedFromThis<FUpdateVersionModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<Model::FVersion> WarningVersionValue;
        TSharedPtr<Model::FVersion> ErrorVersionValue;
        TOptional<FString> ScopeValue;
        TSharedPtr<Model::FVersion> CurrentVersionValue;
        TOptional<bool> NeedSignatureValue;
        TOptional<FString> SignatureKeyIdValue;
        
    public:
        
        FUpdateVersionModelMasterRequest();
        FUpdateVersionModelMasterRequest(
            const FUpdateVersionModelMasterRequest& From
        );
        ~FUpdateVersionModelMasterRequest() = default;

        TSharedPtr<FUpdateVersionModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithWarningVersion(const TSharedPtr<Model::FVersion> WarningVersion);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithErrorVersion(const TSharedPtr<Model::FVersion> ErrorVersion);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithCurrentVersion(const TSharedPtr<Model::FVersion> CurrentVersion);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithNeedSignature(const TOptional<bool> NeedSignature);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithSignatureKeyId(const TOptional<FString> SignatureKeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<Model::FVersion> GetWarningVersion() const;
        TSharedPtr<Model::FVersion> GetErrorVersion() const;
        TOptional<FString> GetScope() const;
        TSharedPtr<Model::FVersion> GetCurrentVersion() const;
        TOptional<bool> GetNeedSignature() const;
        FString GetNeedSignatureString() const;
        TOptional<FString> GetSignatureKeyId() const;

        static TSharedPtr<FUpdateVersionModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateVersionModelMasterRequest, ESPMode::ThreadSafe> FUpdateVersionModelMasterRequestPtr;
}