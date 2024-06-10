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
#include "../Model/Config.h"

namespace Gs2::Ranking2::Request
{
    class FReceiveClusterRankingReceivedRewardRequest;

    class GS2RANKING2_API FReceiveClusterRankingReceivedRewardRequest final : public TSharedFromThis<FReceiveClusterRankingReceivedRewardRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> AccessTokenValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<int64> SeasonValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReceiveClusterRankingReceivedRewardRequest();
        FReceiveClusterRankingReceivedRewardRequest(
            const FReceiveClusterRankingReceivedRewardRequest& From
        );
        ~FReceiveClusterRankingReceivedRewardRequest() = default;

        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithAccessToken(const TOptional<FString> AccessToken);
        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetAccessToken() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReceiveClusterRankingReceivedRewardRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveClusterRankingReceivedRewardRequest, ESPMode::ThreadSafe> FReceiveClusterRankingReceivedRewardRequestPtr;
}