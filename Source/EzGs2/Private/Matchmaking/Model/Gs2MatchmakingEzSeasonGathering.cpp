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

#include "Matchmaking/Model/Gs2MatchmakingEzSeasonGathering.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzSeasonGathering> FEzSeasonGathering::WithSeasonGatheringId(
        const TOptional<FString> SeasonGatheringId
    )
    {
        this->SeasonGatheringIdValue = SeasonGatheringId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonGathering> FEzSeasonGathering::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonGathering> FEzSeasonGathering::WithSeason(
        const TOptional<int64> Season
    )
    {
        this->SeasonValue = Season;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonGathering> FEzSeasonGathering::WithTier(
        const TOptional<int64> Tier
    )
    {
        this->TierValue = Tier;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonGathering> FEzSeasonGathering::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonGathering> FEzSeasonGathering::WithParticipants(
        const TSharedPtr<TArray<FString>> Participants
    )
    {
        this->ParticipantsValue = Participants;
        return SharedThis(this);
    }
    TOptional<FString> FEzSeasonGathering::GetSeasonGatheringId() const
    {
        return SeasonGatheringIdValue;
    }
    TOptional<FString> FEzSeasonGathering::GetSeasonName() const
    {
        return SeasonNameValue;
    }
    TOptional<int64> FEzSeasonGathering::GetSeason() const
    {
        return SeasonValue;
    }

    FString FEzSeasonGathering::GetSeasonString() const
    {
        if (!SeasonValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), SeasonValue.GetValue());
    }
    TOptional<int64> FEzSeasonGathering::GetTier() const
    {
        return TierValue;
    }

    FString FEzSeasonGathering::GetTierString() const
    {
        if (!TierValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TierValue.GetValue());
    }
    TOptional<FString> FEzSeasonGathering::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<FString>> FEzSeasonGathering::GetParticipants() const
    {
        return ParticipantsValue;
    }

    Gs2::Matchmaking::Model::FSeasonGatheringPtr FEzSeasonGathering::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FSeasonGathering>()
            ->WithSeasonGatheringId(SeasonGatheringIdValue)
            ->WithSeasonName(SeasonNameValue)
            ->WithSeason(SeasonValue)
            ->WithTier(TierValue)
            ->WithName(NameValue)
            ->WithParticipants(ParticipantsValue);
    }

    TSharedPtr<FEzSeasonGathering> FEzSeasonGathering::FromModel(const Gs2::Matchmaking::Model::FSeasonGatheringPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSeasonGathering>()
            ->WithSeasonGatheringId(Model->GetSeasonGatheringId())
            ->WithSeasonName(Model->GetSeasonName())
            ->WithSeason(Model->GetSeason())
            ->WithTier(Model->GetTier())
            ->WithName(Model->GetName())
            ->WithParticipants(Model->GetParticipants());
    }
}