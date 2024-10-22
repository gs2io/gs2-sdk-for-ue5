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
    class FCreateClusterRankingReceivedRewardByUserIdRequest;

    class GS2RANKING2_API FCreateClusterRankingReceivedRewardByUserIdRequest final : public TSharedFromThis<FCreateClusterRankingReceivedRewardByUserIdRequest>
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
        
        FCreateClusterRankingReceivedRewardByUserIdRequest();
        FCreateClusterRankingReceivedRewardByUserIdRequest(
            const FCreateClusterRankingReceivedRewardByUserIdRequest& From
        );
        ~FCreateClusterRankingReceivedRewardByUserIdRequest() = default;

        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithTimeOffsetToken(const TOptional<FString> TimeOffsetToken);
        TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> WithDuplicationAvoider(const TOptional<FString> DuplicationAvoider);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetRankingName() const;
        TOptional<FString> GetClusterName() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;
        TOptional<FString> GetTimeOffsetToken() const;
        TOptional<FString> GetDuplicationAvoider() const;

        static TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateClusterRankingReceivedRewardByUserIdRequest> FCreateClusterRankingReceivedRewardByUserIdRequestPtr;
}