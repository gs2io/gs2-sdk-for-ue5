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

#include "Ranking2/Model/Gs2Ranking2EzGlobalRankingScore.h"

namespace Gs2::UE5::Ranking2::Model
{

    TSharedPtr<FEzGlobalRankingScore> FEzGlobalRankingScore::WithRankingName(
        const TOptional<FString> RankingName
    )
    {
        this->RankingNameValue = RankingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingScore> FEzGlobalRankingScore::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingScore> FEzGlobalRankingScore::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingScore> FEzGlobalRankingScore::WithScore(
        const TOptional<int64> Score
    )
    {
        this->ScoreValue = Score;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingScore> FEzGlobalRankingScore::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGlobalRankingScore> FEzGlobalRankingScore::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzGlobalRankingScore::GetRankingName() const
    {
        return RankingNameValue;
    }
    TOptional<int64> FEzGlobalRankingScore::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzGlobalRankingScore::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<FString> FEzGlobalRankingScore::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzGlobalRankingScore::GetScore() const
    {
        return ScoreValue;
    }

    FString FEzGlobalRankingScore::GetScoreString() const
    {
        if (!ScoreValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ScoreValue.GetValue());
    }
    TOptional<FString> FEzGlobalRankingScore::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzGlobalRankingScore::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzGlobalRankingScore::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Ranking2::Model::FGlobalRankingScorePtr FEzGlobalRankingScore::ToModel() const
    {
        return MakeShared<Gs2::Ranking2::Model::FGlobalRankingScore>()
            ->WithRankingName(RankingNameValue)
            ->WithSeason(SeasonValue)
            ->WithUserId(UserIdValue)
            ->WithScore(ScoreValue)
            ->WithMetadata(MetadataValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzGlobalRankingScore> FEzGlobalRankingScore::FromModel(const Gs2::Ranking2::Model::FGlobalRankingScorePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGlobalRankingScore>()
            ->WithRankingName(Model->GetRankingName())
            ->WithSeason(Model->GetSeason())
            ->WithUserId(Model->GetUserId())
            ->WithScore(Model->GetScore())
            ->WithMetadata(Model->GetMetadata())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}