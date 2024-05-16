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

#include "Ranking/Model/GitHubCheckoutSetting.h"

namespace Gs2::Ranking::Model
{
    FGitHubCheckoutSetting::FGitHubCheckoutSetting():
        ApiKeyIdValue(TOptional<FString>()),
        RepositoryNameValue(TOptional<FString>()),
        SourcePathValue(TOptional<FString>()),
        ReferenceTypeValue(TOptional<FString>()),
        CommitHashValue(TOptional<FString>()),
        BranchNameValue(TOptional<FString>()),
        TagNameValue(TOptional<FString>())
    {
    }

    FGitHubCheckoutSetting::FGitHubCheckoutSetting(
        const FGitHubCheckoutSetting& From
    ):
        ApiKeyIdValue(From.ApiKeyIdValue),
        RepositoryNameValue(From.RepositoryNameValue),
        SourcePathValue(From.SourcePathValue),
        ReferenceTypeValue(From.ReferenceTypeValue),
        CommitHashValue(From.CommitHashValue),
        BranchNameValue(From.BranchNameValue),
        TagNameValue(From.TagNameValue)
    {
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::WithApiKeyId(
        const TOptional<FString> ApiKeyId
    )
    {
        this->ApiKeyIdValue = ApiKeyId;
        return SharedThis(this);
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::WithRepositoryName(
        const TOptional<FString> RepositoryName
    )
    {
        this->RepositoryNameValue = RepositoryName;
        return SharedThis(this);
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::WithSourcePath(
        const TOptional<FString> SourcePath
    )
    {
        this->SourcePathValue = SourcePath;
        return SharedThis(this);
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::WithReferenceType(
        const TOptional<FString> ReferenceType
    )
    {
        this->ReferenceTypeValue = ReferenceType;
        return SharedThis(this);
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::WithCommitHash(
        const TOptional<FString> CommitHash
    )
    {
        this->CommitHashValue = CommitHash;
        return SharedThis(this);
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::WithBranchName(
        const TOptional<FString> BranchName
    )
    {
        this->BranchNameValue = BranchName;
        return SharedThis(this);
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::WithTagName(
        const TOptional<FString> TagName
    )
    {
        this->TagNameValue = TagName;
        return SharedThis(this);
    }
    TOptional<FString> FGitHubCheckoutSetting::GetApiKeyId() const
    {
        return ApiKeyIdValue;
    }
    TOptional<FString> FGitHubCheckoutSetting::GetRepositoryName() const
    {
        return RepositoryNameValue;
    }
    TOptional<FString> FGitHubCheckoutSetting::GetSourcePath() const
    {
        return SourcePathValue;
    }
    TOptional<FString> FGitHubCheckoutSetting::GetReferenceType() const
    {
        return ReferenceTypeValue;
    }
    TOptional<FString> FGitHubCheckoutSetting::GetCommitHash() const
    {
        return CommitHashValue;
    }
    TOptional<FString> FGitHubCheckoutSetting::GetBranchName() const
    {
        return BranchNameValue;
    }
    TOptional<FString> FGitHubCheckoutSetting::GetTagName() const
    {
        return TagNameValue;
    }

    TSharedPtr<FGitHubCheckoutSetting> FGitHubCheckoutSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGitHubCheckoutSetting>()
            ->WithApiKeyId(Data->HasField(ANSI_TO_TCHAR("apiKeyId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("apiKeyId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRepositoryName(Data->HasField(ANSI_TO_TCHAR("repositoryName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("repositoryName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSourcePath(Data->HasField(ANSI_TO_TCHAR("sourcePath")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("sourcePath"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithReferenceType(Data->HasField(ANSI_TO_TCHAR("referenceType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("referenceType"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCommitHash(Data->HasField(ANSI_TO_TCHAR("commitHash")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("commitHash"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBranchName(Data->HasField(ANSI_TO_TCHAR("branchName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("branchName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTagName(Data->HasField(ANSI_TO_TCHAR("tagName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("tagName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGitHubCheckoutSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ApiKeyIdValue.IsSet())
        {
            JsonRootObject->SetStringField("apiKeyId", ApiKeyIdValue.GetValue());
        }
        if (RepositoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("repositoryName", RepositoryNameValue.GetValue());
        }
        if (SourcePathValue.IsSet())
        {
            JsonRootObject->SetStringField("sourcePath", SourcePathValue.GetValue());
        }
        if (ReferenceTypeValue.IsSet())
        {
            JsonRootObject->SetStringField("referenceType", ReferenceTypeValue.GetValue());
        }
        if (CommitHashValue.IsSet())
        {
            JsonRootObject->SetStringField("commitHash", CommitHashValue.GetValue());
        }
        if (BranchNameValue.IsSet())
        {
            JsonRootObject->SetStringField("branchName", BranchNameValue.GetValue());
        }
        if (TagNameValue.IsSet())
        {
            JsonRootObject->SetStringField("tagName", TagNameValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGitHubCheckoutSetting::TypeName = "GitHubCheckoutSetting";
}