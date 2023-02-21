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
#include "Ranking/Model/Ranking.h"

namespace Gs2::UE5::Ranking::Model
{
	class EZGS2_API FEzRanking final : public TSharedFromThis<FEzRanking>
	{
        TOptional<int64> RankValue;
        TOptional<int64> IndexValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> ScoreValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;

	public:
        TSharedPtr<FEzRanking> WithRank(const TOptional<int64> Rank);
        TSharedPtr<FEzRanking> WithIndex(const TOptional<int64> Index);
        TSharedPtr<FEzRanking> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzRanking> WithScore(const TOptional<int64> Score);
        TSharedPtr<FEzRanking> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRanking> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<int64> GetRank() const;
        FString GetRankString() const;

        TOptional<int64> GetIndex() const;
        FString GetIndexString() const;

        TOptional<FString> GetUserId() const;

        TOptional<int64> GetScore() const;
        FString GetScoreString() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        Gs2::Ranking::Model::FRankingPtr ToModel() const;
        static TSharedPtr<FEzRanking> FromModel(Gs2::Ranking::Model::FRankingPtr Model);
    };
    typedef TSharedPtr<FEzRanking> FEzRankingPtr;
}