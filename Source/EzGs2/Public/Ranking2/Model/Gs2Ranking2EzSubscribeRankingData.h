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
#include "Ranking2/Model/SubscribeRankingData.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzSubscribeRankingData final : public TSharedFromThis<FEzSubscribeRankingData>
	{
        TOptional<FString> RankingNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> ScorerUserIdValue;
        TOptional<int32> IndexValue;
        TOptional<int32> RankValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzSubscribeRankingData> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FEzSubscribeRankingData> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FEzSubscribeRankingData> WithScorerUserId(const TOptional<FString> ScorerUserId);
        TSharedPtr<FEzSubscribeRankingData> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FEzSubscribeRankingData> WithRank(const TOptional<int32> Rank);
        TSharedPtr<FEzSubscribeRankingData> WithScore(const TOptional<int64> Score);
        TSharedPtr<FEzSubscribeRankingData> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSubscribeRankingData> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetRankingName() const;

        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        TOptional<FString> GetScorerUserId() const;

        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;

        TOptional<int32> GetRank() const;
        FString GetRankString() const;

        TOptional<int64> GetScore() const;
        FString GetScoreString() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Ranking2::Model::FSubscribeRankingDataPtr ToModel() const;
        static TSharedPtr<FEzSubscribeRankingData> FromModel(Gs2::Ranking2::Model::FSubscribeRankingDataPtr Model);
    };
    typedef TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingDataPtr;
}