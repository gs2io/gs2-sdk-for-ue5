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
    class FGetClusterRankingScoreRequest;

    class GS2RANKING2_API FGetClusterRankingScoreRequest final : public TSharedFromThis<FGetClusterRankingScoreRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> SeasonValue;
        
    public:
        
        FGetClusterRankingScoreRequest();
        FGetClusterRankingScoreRequest(
            const FGetClusterRankingScoreRequest& From
        );
        ~FGetClusterRankingScoreRequest() = default;

        TSharedPtr<FGetClusterRankingScoreRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FGetClusterRankingScoreRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FGetClusterRankingScoreRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FGetClusterRankingScoreRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FGetClusterRankingScoreRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FGetClusterRankingScoreRequest> WithSeason(const TOptional<int64> Season);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        static TSharedPtr<FGetClusterRankingScoreRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FGetClusterRankingScoreRequest, ESPMode::ThreadSafe> FGetClusterRankingScoreRequestPtr;
}