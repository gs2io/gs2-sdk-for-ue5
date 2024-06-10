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

#include "Ranking2/Model/Gs2Ranking2EzClusterRankingScore.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::WithClusterName(
        const TOptional<FString> ClusterName
    )
    {
        this->ClusterNameValue = ClusterName;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzClusterRankingScore::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<FString> FEzClusterRankingScore::GetClusterName() const
    {
        return ClusterNameValue;
    }
    TOptional<int64> FEzClusterRankingScore::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzClusterRankingScore::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FEzClusterRankingScore::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzClusterRankingScore::GetScore() const
    {
        return ScoreValue;
    }

    FString FEzClusterRankingScore::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FEzClusterRankingScore::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzClusterRankingScore::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzClusterRankingScore::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Ranking2::Model::FClusterRankingScorePtr FEzClusterRankingScore::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FClusterRankingScore>()
            ->WithRankingName(RankingNameValue)
            ->WithClusterName(ClusterNameValue)
            ->WithSeason(SeasonValue)
            ->WithUserId(UserIdValue)
            ->WithScore(ScoreValue)
            ->WithMetadata(MetadataValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzClusterRankingScore> FEzClusterRankingScore::FromModel(const Gs2::Ranking2::Model::FClusterRankingScorePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzClusterRankingScore>()
            ->WithRankingName(Model->GetRankingName())
            ->WithClusterName(Model->GetClusterName())
            ->WithSeason(Model->GetSeason())
            ->WithUserId(Model->GetUserId())
            ->WithScore(Model->GetScore())
            ->WithMetadata(Model->GetMetadata())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}