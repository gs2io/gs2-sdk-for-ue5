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
    class FCalculateSignatureRequest;

    class GS2VERSION_API FCalculateSignatureRequest final : public TSharedFromThis<FCalculateSignatureRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        TSharedPtr<Model::FVersion> VersionValue;
        
    public:
        
        FCalculateSignatureRequest();
        FCalculateSignatureRequest(
            const FCalculateSignatureRequest& From
        );
        ~FCalculateSignatureRequest() = default;

        TSharedPtr<FCalculateSignatureRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCalculateSignatureRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCalculateSignatureRequest> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FCalculateSignatureRequest> WithVersion(const TSharedPtr<Model::FVersion> Version);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;
        TSharedPtr<Model::FVersion> GetVersion() const;

        static TSharedPtr<FCalculateSignatureRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCalculateSignatureRequest, ESPMode::ThreadSafe> FCalculateSignatureRequestPtr;
}