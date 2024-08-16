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
    class FCreateClusterRankingReceivedRewardRequest;

    class GS2RANKING2_API FCreateClusterRankingReceivedRewardRequest final : public TSharedFromThis<FCreateClusterRankingReceivedRewardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FCreateClusterRankingReceivedRewardRequest();
        FCreateClusterRankingReceivedRewardRequest(
            const FCreateClusterRankingReceivedRewardRequest& From
        );
        ~FCreateClusterRankingReceivedRewardRequest() = default;

        TSharedPtr<FCreateClusterRankingReceivedRewardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateClusterRankingReceivedRewardRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateClusterRankingReceivedRewardRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FCreateClusterRankingReceivedRewardRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FCreateClusterRankingReceivedRewardRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FCreateClusterRankingReceivedRewardRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FCreateClusterRankingReceivedRewardRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateClusterRankingReceivedRewardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateClusterRankingReceivedRewardRequest> FCreateClusterRankingReceivedRewardRequestPtr;
}