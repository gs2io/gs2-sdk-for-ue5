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
#include "Matchmaking/Model/JoinedSeasonGathering.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzJoinedSeasonGathering final : public TSharedFromThis<FEzJoinedSeasonGathering>
	{
        TOptional<FString> SeasonNameValue;
        TOptional<int64> SeasonValue;
        TOptional<int64> TierValue;
        TOptional<FString> SeasonGatheringNameValue;

	public:
        TSharedPtr<FEzJoinedSeasonGathering> WithSeasonName(const TOptional<FString> SeasonName);
        TSharedPtr<FEzJoinedSeasonGathering> WithSeason(const TOptional<int64> Season);
        TSharedPtr<FEzJoinedSeasonGathering> WithTier(const TOptional<int64> Tier);
        TSharedPtr<FEzJoinedSeasonGathering> WithSeasonGatheringName(const TOptional<FString> SeasonGatheringName);

        TOptional<FString> GetSeasonName() const;

        TOptional<int64> GetSeason() const;
        FString GetSeasonString() const;

        TOptional<int64> GetTier() const;
        FString GetTierString() const;

        TOptional<FString> GetSeasonGatheringName() const;

        Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr ToModel() const;
        static TSharedPtr<FEzJoinedSeasonGathering> FromModel(Gs2::Matchmaking::Model::FJoinedSeasonGatheringPtr Model);
    };
    typedef TSharedPtr<FEzJoinedSeasonGathering> FEzJoinedSeasonGatheringPtr;
}