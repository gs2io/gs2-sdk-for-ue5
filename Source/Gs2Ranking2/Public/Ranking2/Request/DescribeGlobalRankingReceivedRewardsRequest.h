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
    class FDescribeGlobalRankingReceivedRewardsRequest;

    class GS2RANKING2_API FDescribeGlobalRankingReceivedRewardsRequest final : public TSharedFromThis<FDescribeGlobalRankingReceivedRewardsRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RankingNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeGlobalRankingReceivedRewardsRequest();
        FDescribeGlobalRankingReceivedRewardsRequest(
            const FDescribeGlobalRankingReceivedRewardsRequest& From
        );
        ~FDescribeGlobalRankingReceivedRewardsRequest() = default;

        TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRankingName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeGlobalRankingReceivedRewardsRequest, ESPMode::ThreadSafe> FDescribeGlobalRankingReceivedRewardsRequestPtr;
}