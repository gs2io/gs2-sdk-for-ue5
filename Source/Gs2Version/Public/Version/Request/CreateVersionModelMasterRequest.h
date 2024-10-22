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
#include "Dom/JsonObject.h"
#include "../Model/Version.h"
#include "../Model/ScheduleVersion.h"

namespace Gs2::Version::Request
{
    class FCreateVersionModelMasterRequest;

    class GS2VERSION_API FCreateVersionModelMasterRequest final : public TSharedFromThis<FCreateVersionModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
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
        
        FCreateVersionModelMasterRequest();
        FCreateVersionModelMasterRequest(
            const FCreateVersionModelMasterRequest& From
        );
        ~FCreateVersionModelMasterRequest() = default;

        TSharedPtr<FCreateVersionModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateVersionModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateVersionModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateVersionModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateVersionModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateVersionModelMasterRequest> WithScope(const TOptional<FString> Scope);
        TSharedPtr<FCreateVersionModelMasterRequest> WithType(const TOptional<FString> Type);
        TSharedPtr<FCreateVersionModelMasterRequest> WithCurrentVersion(const TSharedPtr<Model::FVersion> CurrentVersion);
        TSharedPtr<FCreateVersionModelMasterRequest> WithWarningVersion(const TSharedPtr<Model::FVersion> WarningVersion);
        TSharedPtr<FCreateVersionModelMasterRequest> WithErrorVersion(const TSharedPtr<Model::FVersion> ErrorVersion);
        TSharedPtr<FCreateVersionModelMasterRequest> WithScheduleVersions(const TSharedPtr<TArray<TSharedPtr<Model::FScheduleVersion>>> ScheduleVersions);
        TSharedPtr<FCreateVersionModelMasterRequest> WithNeedSignature(const TOptional<bool> NeedSignature);
        TSharedPtr<FCreateVersionModelMasterRequest> WithSignatureKeyId(const TOptional<FString> SignatureKeyId);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
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

        static TSharedPtr<FCreateVersionModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateVersionModelMasterRequest> FCreateVersionModelMasterRequestPtr;
}