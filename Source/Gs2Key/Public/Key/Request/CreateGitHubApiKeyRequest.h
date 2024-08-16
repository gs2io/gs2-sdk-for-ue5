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

namespace Gs2::Key::Request
{
    class FCreateGitHubApiKeyRequest;

    class GS2KEY_API FCreateGitHubApiKeyRequest final : public TSharedFromThis<FCreateGitHubApiKeyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ApiKeyValue;
        TOptional<FString> EncryptionKeyNameValue;
        
    public:
        
        FCreateGitHubApiKeyRequest();
        FCreateGitHubApiKeyRequest(
            const FCreateGitHubApiKeyRequest& From
        );
        ~FCreateGitHubApiKeyRequest() = default;

        TSharedPtr<FCreateGitHubApiKeyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateGitHubApiKeyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateGitHubApiKeyRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateGitHubApiKeyRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateGitHubApiKeyRequest> WithApiKey(const TOptional<FString> ApiKey);
        TSharedPtr<FCreateGitHubApiKeyRequest> WithEncryptionKeyName(const TOptional<FString> EncryptionKeyName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetApiKey() const;
        TOptional<FString> GetEncryptionKeyName() const;

        static TSharedPtr<FCreateGitHubApiKeyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateGitHubApiKeyRequest> FCreateGitHubApiKeyRequestPtr;
}