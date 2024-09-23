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
#include "../Model/ScheduleVersion.h"

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
        TOptional<FString> ScopeValue;
        TOptional<FString> TypeValue;
        TSharedPtr<Model::FVersion> CurrentVersionValue;
        TSharedPtr<Model::FVersion> WarningVersionValue;
        TSharedPtr<Model::FVersion> ErrorVersionValue;
        TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> ScheduleVersionsValue;
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
        TSharedPtr<FUpdateVersionModelMasterRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithType(const TOptional<FString> Type);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithCurrentVersion(const TSharedPtr<Model::FVersion> CurrentVersion);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithWarningVersion(const TSharedPtr<Model::FVersion> WarningVersion);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithErrorVersion(const TSharedPtr<Model::FVersion> ErrorVersion);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithScheduleVersions(const TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> ScheduleVersions);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithNeedSignature(const TOptional<bool> NeedSignature);
        TSharedPtr<FUpdateVersionModelMasterRequest> WithSignatureKeyId(const TOptional<FString> SignatureKeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetScope() const;
        TOptional<FString> GetType() const;
        TSharedPtr<Model::FVersion> GetCurrentVersion() const;
        TSharedPtr<Model::FVersion> GetWarningVersion() const;
        TSharedPtr<Model::FVersion> GetErrorVersion() const;TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> GetScheduleVersions() const;
        TOptional<bool> GetNeedSignature() const;
        FString GetNeedSignatureString() const;
        TOptional<FString> GetSignatureKeyId() const;

        static TSharedPtr<FUpdateVersionModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateVersionModelMasterRequest, ESPMode::ThreadSafe> FUpdateVersionModelMasterRequestPtr;
}