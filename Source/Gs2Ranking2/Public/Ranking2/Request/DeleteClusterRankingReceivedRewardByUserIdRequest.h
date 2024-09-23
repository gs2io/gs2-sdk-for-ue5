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
    class FDeleteClusterRankingReceivedRewardByUserIdRequest;

    class GS2RANKING2_API FDeleteClusterRankingReceivedRewardByUserIdRequest final : public TSharedFromThis<FDeleteClusterRankingReceivedRewardByUserIdRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> TimeOffsetTokenValue;
        TOptional<FString> DuplicationAvoiderValue;
        
    public:
        
        FDeleteClusterRankingReceivedRewardByUserIdRequest();
        FDeleteClusterRankingReceivedRewardByUserIdRequest(
            const FDeleteClusterRankingReceivedRewardByUserIdRequest& From
        );
        ~FDeleteClusterRankingReceivedRewardByUserIdRequest() = default;

        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDeleteClusterRankingReceivedRewardByUserIdRequest, ESPMode::ThreadSafe> FDeleteClusterRankingReceivedRewardByUserIdRequestPtr;
}