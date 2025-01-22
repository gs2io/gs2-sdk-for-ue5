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

#include "Ranking2/Model/Gs2Ranking2EzSubscribeRankingData.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithScorerUserId(
        const TOptional<FString> ScorerUserId
    )
    {
        this->ScorerUserIdValue = ScorerUserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithRank(
        const TOptional<int32> Rank
    )
    {
        this->RankValue = Rank;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzSubscribeRankingData::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<int64> FEzSubscribeRankingData::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzSubscribeRankingData::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FEzSubscribeRankingData::GetScorerUserId() const
    {
        return ScorerUserIdValue;
    }
    TOptional<int32> FEzSubscribeRankingData::GetIndex() const
    {
        return IndexValue;
    }

    FString FEzSubscribeRankingData::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IndexValue.GetValue());
    }
    TOptional<int32> FEzSubscribeRankingData::GetRank() const
    {
        return RankValue;
    }

    FString FEzSubscribeRankingData::GetRankString() const
    {
        if (!RankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RankValue.GetValue());
    }
    TOptional<int64> FEzSubscribeRankingData::GetScore() const
    {
        return ScoreValue;
    }

    FString FEzSubscribeRankingData::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FEzSubscribeRankingData::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzSubscribeRankingData::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzSubscribeRankingData::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Ranking2::Model::FSubscribeRankingDataPtr FEzSubscribeRankingData::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FSubscribeRankingData>()
            ->WithRankingName(RankingNameValue)
            ->WithSeason(SeasonValue)
            ->WithScorerUserId(ScorerUserIdValue)
            ->WithIndex(IndexValue)
            ->WithRank(RankValue)
            ->WithScore(ScoreValue)
            ->WithMetadata(MetadataValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzSubscribeRankingData> FEzSubscribeRankingData::FromModel(const Gs2::Ranking2::Model::FSubscribeRankingDataPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSubscribeRankingData>()
            ->WithRankingName(Model->GetRankingName())
            ->WithSeason(Model->GetSeason())
            ->WithScorerUserId(Model->GetScorerUserId())
            ->WithIndex(Model->GetIndex())
            ->WithRank(Model->GetRank())
            ->WithScore(Model->GetScore())
            ->WithMetadata(Model->GetMetadata())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}