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

#include "Ranking2/Model/Gs2Ranking2EzClusterRankingData.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithClusterName(
        const TOptional<FString> ClusterName
    )
    {
        this->ClusterNameValue = ClusterName;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithIndex(
        const TOptional<int32> Index
    )
    {
        this->IndexValue = Index;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithRank(
        const TOptional<int32> Rank
    )
    {
        this->RankValue = Rank;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzClusterRankingData::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<FString> FEzClusterRankingData::GetClusterName() const
    {
        return ClusterNameValue;
    }
    TOptional<int64> FEzClusterRankingData::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzClusterRankingData::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FEzClusterRankingData::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int32> FEzClusterRankingData::GetIndex() const
    {
        return IndexValue;
    }

    FString FEzClusterRankingData::GetIndexString() const
    {
        if (!IndexValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IndexValue.GetValue());
    }
    TOptional<int32> FEzClusterRankingData::GetRank() const
    {
        return RankValue;
    }

    FString FEzClusterRankingData::GetRankString() const
    {
        if (!RankValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RankValue.GetValue());
    }
    TOptional<int64> FEzClusterRankingData::GetScore() const
    {
        return ScoreValue;
    }

    FString FEzClusterRankingData::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FEzClusterRankingData::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzClusterRankingData::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzClusterRankingData::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Ranking2::Model::FClusterRankingDataPtr FEzClusterRankingData::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FClusterRankingData>()
            ->WithRankingName(RankingNameValue)
            ->WithClusterName(ClusterNameValue)
            ->WithSeason(SeasonValue)
            ->WithUserId(UserIdValue)
            ->WithIndex(IndexValue)
            ->WithRank(RankValue)
            ->WithScore(ScoreValue)
            ->WithMetadata(MetadataValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzClusterRankingData> FEzClusterRankingData::FromModel(const Gs2::Ranking2::Model::FClusterRankingDataPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzClusterRankingData>()
            ->WithRankingName(Model->GetRankingName())
            ->WithClusterName(Model->GetClusterName())
            ->WithSeason(Model->GetSeason())
            ->WithUserId(Model->GetUserId())
            ->WithIndex(Model->GetIndex())
            ->WithRank(Model->GetRank())
            ->WithScore(Model->GetScore())
            ->WithMetadata(Model->GetMetadata())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}