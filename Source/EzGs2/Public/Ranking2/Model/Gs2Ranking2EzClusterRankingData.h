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
#include "Ranking2/Model/ClusterRankingData.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzClusterRankingData final : public TSharedFromThis<FEzClusterRankingData>
	{
        TOptional<FString> RankingNameValue;
        TOptional<FString> ClusterNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> IndexValue;
        TOptional<int32> RankValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzClusterRankingData> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FEzClusterRankingData> WithClusterName(const TOptional<FString> ClusterName);
        TSharedPtr<FEzClusterRankingData> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FEzClusterRankingData> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzClusterRankingData> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FEzClusterRankingData> WithRank(const TOptional<int32> Rank);
        TSharedPtr<FEzClusterRankingData> WithScore(const TOptional<int64> Score);
        TSharedPtr<FEzClusterRankingData> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzClusterRankingData> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetRankingName() const;

        TOptional<FString> GetClusterName() const;

        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        TOptional<FString> GetUserId() const;

        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;

        TOptional<int32> GetRank() const;
        FString GetRankString() const;

        TOptional<int64> GetScore() const;
        FString GetScoreString() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Ranking2::Model::FClusterRankingDataPtr ToModel() const;
        static TSharedPtr<FEzClusterRankingData> FromModel(Gs2::Ranking2::Model::FClusterRankingDataPtr Model);
    };
    typedef TSharedPtr<FEzClusterRankingData> FEzClusterRankingDataPtr;
}