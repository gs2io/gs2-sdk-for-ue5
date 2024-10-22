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

namespace Gs2::SerialKey::Request
{
    class FGetIssueJobRequest;

    class GS2SERIALKEY_API FGetIssueJobRequest final : public TSharedFromThis<FGetIssueJobRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CampaignModelNameValue;
        TOptional<FString> IssueJobNameValue;
        
    public:
        
        FGetIssueJobRequest();
        FGetIssueJobRequest(
            const FGetIssueJobRequest& From
        );
        ~FGetIssueJobRequest() = default;

        TSharedPtr<FGetIssueJobRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetIssueJobRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetIssueJobRequest> WithCampaignModelName(const TOptional<FString> CampaignModelName);
        TSharedPtr<FGetIssueJobRequest> WithIssueJobName(const TOptional<FString> IssueJobName);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCampaignModelName() const;
        TOptional<FString> GetIssueJobName() const;

        static TSharedPtr<FGetIssueJobRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetIssueJobRequest> FGetIssueJobRequestPtr;
}