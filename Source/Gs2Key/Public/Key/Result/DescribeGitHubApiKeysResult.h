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
#include "../Model/GitHubApiKey.h"

namespace Gs2::Key::Result
{
    class GS2KEY_API FDescribeGitHubApiKeysResult final : public TSharedFromThis<FDescribeGitHubApiKeysResult>
    {
        TSharedPtr<TArray<TSharedPtr<Model::FGitHubApiKey>>> ItemsValue;
        TOptional<FString> NextPageTokenValue;
        
    public:
        
        FDescribeGitHubApiKeysResult();
        FDescribeGitHubApiKeysResult(
            const FDescribeGitHubApiKeysResult& From
        );
        ~FDescribeGitHubApiKeysResult() = default;

        TSharedPtr<FDescribeGitHubApiKeysResult> WithItems(const TSharedPtr<TArray<TSharedPtr<Model::FGitHubApiKey>>> Items);
        TSharedPtr<FDescribeGitHubApiKeysResult> WithNextPageToken(const TOptional<FString> NextPageToken);

        TSharedPtr<TArray<TSharedPtr<Model::FGitHubApiKey>>> GetItems() const;
        TOptional<FString> GetNextPageToken() const;

        static TSharedPtr<FDescribeGitHubApiKeysResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGitHubApiKeysResult, ESPMode::ThreadSafe> FDescribeGitHubApiKeysResultPtr;
}