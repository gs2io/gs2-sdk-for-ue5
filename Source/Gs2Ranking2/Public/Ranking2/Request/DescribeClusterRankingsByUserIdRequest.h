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

namespace Gs2::Ranking2::Request
{
    class FDescribeClusterRankingsByUserIdRequest;

    class GS2RANKING2_API FDescribeClusterRankingsByUserIdRequest final : public TSharedFromThis<FDescribeClusterRankingsByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        TOptional<FString> TimeOffsetTokenValue;
        
    public:
        
        FDescribeClusterRankingsByUserIdRequest();
        FDescribeClusterRankingsByUserIdRequest(
            const FDescribeClusterRankingsByUserIdRequest& From
        );
        ~FDescribeClusterRankingsByUserIdRequest() = default;

        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeClusterRankingsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;
        TOptional<FString> GetTimeOffsetToken() const;

        static TSharedPtr<FDescribeClusterRankingsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeClusterRankingsByUserIdRequest, ESPMode::ThreadSafe> FDescribeClusterRankingsByUserIdRequestPtr;
}