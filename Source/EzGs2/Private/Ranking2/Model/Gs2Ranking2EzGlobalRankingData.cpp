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

#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingData.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithRank(
        const TOptional<int32> Rank
    )
    {
        this->RankValue = Rank;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzGlobalRankingData::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<int64> FEzGlobalRankingData::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzGlobalRankingData::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FEzGlobalRankingData::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FEzGlobalRankingData::GetIndex() const
    {
        return IndexValue;
    }

    FString FEzGlobalRankingData::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IndexValue.GetValue());
    }
    TOptional<int32> FEzGlobalRankingData::GetRank() const
    {
        return RankValue;
    }

    FString FEzGlobalRankingData::GetRankString() const
    {
        if (!RankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RankValue.GetValue());
    }
    TOptional<int64> FEzGlobalRankingData::GetScore() const
    {
        return ScoreValue;
    }

    FString FEzGlobalRankingData::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FEzGlobalRankingData::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzGlobalRankingData::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzGlobalRankingData::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Ranking2::Model::FGlobalRankingDataPtr FEzGlobalRankingData::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FGlobalRankingData>()
            ->WithRankingName(RankingNameValue)
            ->WithSeason(SeasonValue)
            ->WithUserId(UserIdValue)
            ->WithIndex(IndexValue)
            ->WithRank(RankValue)
            ->WithScore(ScoreValue)
            ->WithMetadata(MetadataValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzGlobalRankingData> FEzGlobalRankingData::FromModel(const Gs2::Ranking2::Model::FGlobalRankingDataPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGlobalRankingData>()
            ->WithRankingName(Model->GetRankingName())
            ->WithSeason(Model->GetSeason())
            ->WithUserId(Model->GetUserId())
            ->WithIndex(Model->GetIndex())
            ->WithRank(Model->GetRank())
            ->WithScore(Model->GetScore())
            ->WithMetadata(Model->GetMetadata())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}