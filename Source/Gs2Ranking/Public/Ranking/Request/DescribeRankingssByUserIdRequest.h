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
    class FDescribeRankingssByUserIdRequest;

    class GS2RANKING_API FDescribeRankingssByUserIdRequest final : public TSharedFromThis<FDescribeRankingssByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CategoryNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> AdditionalScopeNameValue;
        TOptional<int64> StartIndexValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeRankingssByUserIdRequest();
        FDescribeRankingssByUserIdRequest(
            const FDescribeRankingssByUserIdRequest& From
        );
        ~FDescribeRankingssByUserIdRequest() = default;

        TSharedPtr<FDescribeRankingssByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeRankingssByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeRankingssByUserIdRequest> WithCategoryName(const TOptional<FString> CategoryName);
        TSharedPtr<FDescribeRankingssByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeRankingssByUserIdRequest> WithAdditionalScopeName(const TOptional<FString> AdditionalScopeName);
        TSharedPtr<FDescribeRankingssByUserIdRequest> WithStartIndex(const TOptional<int64> StartIndex);
        TSharedPtr<FDescribeRankingssByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeRankingssByUserIdRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCategoryName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetAdditionalScopeName() const;
        TOptional<int64> GetStartIndex() const;
        FString GetStartIndexString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeRankingssByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeRankingssByUserIdRequest, ESPMode::ThreadSafe> FDescribeRankingssByUserIdRequestPtr;
}