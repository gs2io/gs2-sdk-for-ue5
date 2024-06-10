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
#include "Ranking2/Model/SubscribeRankingScore.h"

namespace Gs2::UE5::Ranking2::Model
{
	class EZGS2_API FEzSubscribeRankingScore final : public TSharedFromThis<FEzSubscribeRankingScore>
	{
        TOptional<FString> RankingNameValue;
        TOptional<int64> SeasonValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzSubscribeRankingScore> WithRankingName(const TOptional<FString> RankingName);
        TSharedPtr<FEzSubscribeRankingScore> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FEzSubscribeRankingScore> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzSubscribeRankingScore> WithScore(const TOptional<int64> Score);
        TSharedPtr<FEzSubscribeRankingScore> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSubscribeRankingScore> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetRankingName() const;

        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        TOptional<FString> GetUserId() const;

        TOptional<int64> GetScore() const;
        FString GetScoreString() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Ranking2::Model::FSubscribeRankingScorePtr ToModel() const;
        static TSharedPtr<FEzSubscribeRankingScore> FromModel(Gs2::Ranking2::Model::FSubscribeRankingScorePtr Model);
    };
    typedef TSharedPtr<FEzSubscribeRankingScore> FEzSubscribeRankingScorePtr;
}