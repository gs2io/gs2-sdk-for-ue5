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
    class FDescribeIssueJobsRequest;

    class GS2SERIALKEY_API FDescribeIssueJobsRequest final : public TSharedFromThis<FDescribeIssueJobsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CampaignModelNameValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeIssueJobsRequest();
        FDescribeIssueJobsRequest(
            const FDescribeIssueJobsRequest& From
        );
        ~FDescribeIssueJobsRequest() = default;

        TSharedPtr<FDescribeIssueJobsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeIssueJobsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeIssueJobsRequest> WithCampaignModelName(const TOptional<FString> CampaignModelName);
        TSharedPtr<FDescribeIssueJobsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeIssueJobsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCampaignModelName() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeIssueJobsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeIssueJobsRequest> FDescribeIssueJobsRequestPtr;
}