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

#include "Matchmaking/Model/Gs2MatchmakingEzJoinedSeasonGathering.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzJoinedSeasonGathering> FEzJoinedSeasonGathering::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FEzJoinedSeasonGathering> FEzJoinedSeasonGathering::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzJoinedSeasonGathering> FEzJoinedSeasonGathering::WithTier(
        const TOptional<int64> Tier
    )
    {
        this->TierValue = Tier;
        return SharedThis(this);
    }

    TSharedPtr<FEzJoinedSeasonGathering> FEzJoinedSeasonGathering::WithSeasonGatheringName(
        const TOptional<FString> SeasonGatheringName
    )
    {
        this->SeasonGatheringNameValue = SeasonGatheringName;
        return SharedThis(this);
    }
    TOptional<FString> FEzJoinedSeasonGathering::GetSeasonName() const
    {
        return SeasonNameValue;
    }
    TOptional<int64> FEzJoinedSeasonGathering::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzJoinedSeasonGathering::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<int64> FEzJoinedSeasonGathering::GetTier() const
    {
        return TierValue;
    }

    FString FEzJoinedSeasonGathering::GetTierString() const
    {
        if (!TierValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TierValue.GetValue());
    }
    TOptional<FString> FEzJoinedSeasonGathering::GetSeasonGatheringName() const
    {
        return SeasonGatheringNameValue;
    }

    Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr FEzJoinedSeasonGathering::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FJoinedSeasonGathering>()
            ->WithSeasonName(SeasonNameValue)
            ->WithSeason(SeasonValue)
            ->WithTier(TierValue)
            ->WithSeasonGatheringName(SeasonGatheringNameValue);
    }

    TSharedPtr<FEzJoinedSeasonGathering> FEzJoinedSeasonGathering::FromModel(const Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzJoinedSeasonGathering>()
            ->WithSeasonName(Model->GetSeasonName())
            ->WithSeason(Model->GetSeason())
            ->WithTier(Model->GetTier())
            ->WithSeasonGatheringName(Model->GetSeasonGatheringName());
    }
}