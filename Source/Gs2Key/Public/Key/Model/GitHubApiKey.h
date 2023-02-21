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

namespace Gs2::Key::Model
{
    class GS2KEY_API FGitHubApiKey final : public TSharedFromThis<FGitHubApiKey>
    {
        TOptional<FString> ApiKeyIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> EncryptionKeyNameValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FGitHubApiKey();
        FGitHubApiKey(
            const FGitHubApiKey& From
        );
        ~FGitHubApiKey() = default;

        TSharedPtr<FGitHubApiKey> WithApiKeyId(const TOptional<FString> ApiKeyId);
        TSharedPtr<FGitHubApiKey> WithName(const TOptional<FString> Name);
        TSharedPtr<FGitHubApiKey> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FGitHubApiKey> WithEncryptionKeyName(const TOptional<FString> EncryptionKeyName);
        TSharedPtr<FGitHubApiKey> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGitHubApiKey> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetApiKeyId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetEncryptionKeyName() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetApiKeyNameFromGrn(const FString Grn);

        static TSharedPtr<FGitHubApiKey> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGitHubApiKey, ESPMode::ThreadSafe> FGitHubApiKeyPtr;
}