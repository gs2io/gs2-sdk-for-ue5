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

namespace Gs2::Key::Request
{
    class FDeleteGitHubApiKeyRequest;

    class GS2KEY_API FDeleteGitHubApiKeyRequest final : public TSharedFromThis<FDeleteGitHubApiKeyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> ApiKeyNameValue;
        
    public:
        
        FDeleteGitHubApiKeyRequest();
        FDeleteGitHubApiKeyRequest(
            const FDeleteGitHubApiKeyRequest& From
        );
        ~FDeleteGitHubApiKeyRequest() = default;

        TSharedPtr<FDeleteGitHubApiKeyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteGitHubApiKeyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteGitHubApiKeyRequest> WithApiKeyName(const TOptional<FString> ApiKeyName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetApiKeyName() const;

        static TSharedPtr<FDeleteGitHubApiKeyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteGitHubApiKeyRequest, ESPMode::ThreadSafe> FDeleteGitHubApiKeyRequestPtr;
}