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
    class FGetClusterRankingReceivedRewardRequest;

    class GS2RANKING2_API FGetClusterRankingReceivedRewardRequest final : public TSharedFromThis<FGetClusterRankingReceivedRewardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> SeasonValue;
        
    public:
        
        FGetClusterRankingReceivedRewardRequest();
        FGetClusterRankingReceivedRewardRequest(
            const FGetClusterRankingReceivedRewardRequest& From
        );
        ~FGetClusterRankingReceivedRewardRequest() = default;

        TSharedPtr<FGetClusterRankingReceivedRewardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetClusterRankingReceivedRewardRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetClusterRankingReceivedRewardRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGetClusterRankingReceivedRewardRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FGetClusterRankingReceivedRewardRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetClusterRankingReceivedRewardRequest> WithSeason(const TOptional<int64> Season);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        static TSharedPtr<FGetClusterRankingReceivedRewardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetClusterRankingReceivedRewardRequest, ESPMode::ThreadSafe> FGetClusterRankingReceivedRewardRequestPtr;
}