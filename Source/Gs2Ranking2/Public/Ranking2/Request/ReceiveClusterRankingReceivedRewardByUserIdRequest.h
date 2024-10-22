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
#include "../Model/Config.h"

namespace Gs2::Ranking2::Request
{
    class FReceiveClusterRankingReceivedRewardByUserIdRequest;

    class GS2RANKING2_API FReceiveClusterRankingReceivedRewardByUserIdRequest final : public TSharedFromThis<FReceiveClusterRankingReceivedRewardByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<int64> SeasonValue;
        TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> ConfigValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FReceiveClusterRankingReceivedRewardByUserIdRequest();
        FReceiveClusterRankingReceivedRewardByUserIdRequest(
            const FReceiveClusterRankingReceivedRewardByUserIdRequest& From
        );
        ~FReceiveClusterRankingReceivedRewardByUserIdRequest() = default;

        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithConfig(const TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> Config);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetUserId() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;TSharedPtr<TArray<TSharedPtr<Model::FConfig>>> GetConfig() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FReceiveClusterRankingReceivedRewardByUserIdRequest> FReceiveClusterRankingReceivedRewardByUserIdRequestPtr;
}