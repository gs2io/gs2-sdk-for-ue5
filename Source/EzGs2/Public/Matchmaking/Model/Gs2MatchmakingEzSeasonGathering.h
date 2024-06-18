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
#include "Matchmaking/Model/SeasonGathering.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzSeasonGathering final : public TSharedFromThis<FEzSeasonGathering>
	{
        TOptional<FString> SeasonGatheringIdValue;
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> TierValue;
        TOptional<FString> NameValue;
        TSharedPtr<TArray<FString>> ParticipantsValue;

	public:
        TSharedPtr<FEzSeasonGathering> WithSeasonGatheringId(const TOptional<FString> SeasonGatheringId);
        TSharedPtr<FEzSeasonGathering> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FEzSeasonGathering> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FEzSeasonGathering> WithTier(const TOptional<int64> Tier);
        TSharedPtr<FEzSeasonGathering> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzSeasonGathering> WithParticipants(const TSharedPtr<TArray<FString>> Participants);

        TOptional<FString> GetSeasonGatheringId() const;

        TOptional<FString> GetSeasonName() const;

        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        TOptional<int64> GetTier() const;
        FString GetTierString() const;

        TOptional<FString> GetName() const;

        TSharedPtr<TArray<FString>> GetParticipants() const;

        Gs2::Matchmaking::Model::FSeasonGatheringPtr ToModel() const;
        static TSharedPtr<FEzSeasonGathering> FromModel(Gs2::Matchmaking::Model::FSeasonGatheringPtr Model);
    };
    typedef TSharedPtr<FEzSeasonGathering> FEzSeasonGatheringPtr;
}