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
#include "Ranking2/Model/ClusterRankingReceivedReward.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzClusterRankingReceivedReward final : public TSharedFromThis<FEzClusterRankingReceivedReward>
	{
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ReceivedAtValue;

	public:
        TSharedPtr<FEzClusterRankingReceivedReward> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FEzClusterRankingReceivedReward> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FEzClusterRankingReceivedReward> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FEzClusterRankingReceivedReward> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzClusterRankingReceivedReward> WithReceivedAt(const TOptional<int64> ReceivedAt);

        TOptional<FString> GetRankingName() const;

        TOptional<FString> GetClusterName() const;

        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        TOptional<FString> GetUserId() const;

        TOptional<int64> GetReceivedAt() const;
        FString GetReceivedAtString() const;

        Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr ToModel() const;
        static TSharedPtr<FEzClusterRankingReceivedReward> FromModel(Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr Model);
    };
    typedef TSharedPtr<FEzClusterRankingReceivedReward> FEzClusterRankingReceivedRewardPtr;
}