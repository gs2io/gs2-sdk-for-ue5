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

namespace Gs2::Enhance::Model
{
    class GS2ENHANCE_API FGitHubCheckoutSetting final : public FGs2Object, public TSharedFromThis<FGitHubCheckoutSetting>
    {
        TOptional<FString> ApiKeyIdValue;
        TOptional<FString> RepositoryNameValue;
        TOptional<FString> SourcePathValue;
        TOptional<FString> ReferenceTypeValue;
        TOptional<FString> CommitHashValue;
        TOptional<FString> BranchNameValue;
        TOptional<FString> TagNameValue;

    public:
        FGitHubCheckoutSetting();
        FGitHubCheckoutSetting(
            const FGitHubCheckoutSetting& From
        );
        virtual ~FGitHubCheckoutSetting() override = default;

        TSharedPtr<FGitHubCheckoutSetting> WithApiKeyId(const TOptional<FString> ApiKeyId);
        TSharedPtr<FGitHubCheckoutSetting> WithRepositoryName(const TOptional<FString> RepositoryName);
        TSharedPtr<FGitHubCheckoutSetting> WithSourcePath(const TOptional<FString> SourcePath);
        TSharedPtr<FGitHubCheckoutSetting> WithReferenceType(const TOptional<FString> ReferenceType);
        TSharedPtr<FGitHubCheckoutSetting> WithCommitHash(const TOptional<FString> CommitHash);
        TSharedPtr<FGitHubCheckoutSetting> WithBranchName(const TOptional<FString> BranchName);
        TSharedPtr<FGitHubCheckoutSetting> WithTagName(const TOptional<FString> TagName);

        TOptional<FString> GetApiKeyId() const;
        TOptional<FString> GetRepositoryName() const;
        TOptional<FString> GetSourcePath() const;
        TOptional<FString> GetReferenceType() const;
        TOptional<FString> GetCommitHash() const;
        TOptional<FString> GetBranchName() const;
        TOptional<FString> GetTagName() const;


        static TSharedPtr<FGitHubCheckoutSetting> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGitHubCheckoutSetting, ESPMode::ThreadSafe> FGitHubCheckoutSettingPtr;
}