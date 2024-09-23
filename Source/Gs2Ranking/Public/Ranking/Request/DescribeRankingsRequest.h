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

namespace Gs2::Ranking::Request
{
    class FDescribeRankingsRequest;

    class GS2RANKING_API FDescribeRankingsRequest final : public TSharedFromThis<FDescribeRankingsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> AdditionalScopeNameValue;
        TOptional<int64> StartIndexValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeRankingsRequest();
        FDescribeRankingsRequest(
            const FDescribeRankingsRequest& From
        );
        ~FDescribeRankingsRequest() = default;

        TSharedPtr<FDescribeRankingsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeRankingsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeRankingsRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FDescribeRankingsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeRankingsRequest> WithAdditionalScopeName(const TOptional<FString> AdditionalScopeName);
        TSharedPtr<FDescribeRankingsRequest> WithStartIndex(const TOptional<int64> StartIndex);
        TSharedPtr<FDescribeRankingsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeRankingsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetAdditionalScopeName() const;
        TOptional<int64> GetStartIndex() const;
        FString GetStartIndexString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeRankingsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRankingsRequest, ESPMode::ThreadSafe> FDescribeRankingsRequestPtr;
}