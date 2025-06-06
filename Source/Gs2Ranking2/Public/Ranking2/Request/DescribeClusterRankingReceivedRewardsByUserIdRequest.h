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

namespace Gs2::Ranking2::Request
{
    class FDescribeClusterRankingReceivedRewardsByUserIdRequest;

    class GS2RANKING2_API FDescribeClusterRankingReceivedRewardsByUserIdRequest final : public TSharedFromThis<FDescribeClusterRankingReceivedRewardsByUserIdRequest>
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
        
        FDescribeClusterRankingReceivedRewardsByUserIdRequest();
        FDescribeClusterRankingReceivedRewardsByUserIdRequest(
            const FDescribeClusterRankingReceivedRewardsByUserIdRequest& From
        );
        ~FDescribeClusterRankingReceivedRewardsByUserIdRequest() = default;

        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithLimit(const TOptional<int32> Limit);
        TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);

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

        static TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeClusterRankingReceivedRewardsByUserIdRequest> FDescribeClusterRankingReceivedRewardsByUserIdRequestPtr;
}