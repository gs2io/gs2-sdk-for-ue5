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
#include "Matchmaking/Model/SeasonModel.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzSeasonModel final : public TSharedFromThis<FEzSeasonModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> MaximumParticipantsValue;
        TOptional<FString> ExperienceModelIdValue;
        TOptional<FString> ChallengePeriodEventIdValue;

	public:
        TSharedPtr<FEzSeasonModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzSeasonModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSeasonModel> WithMaximumParticipants(const TOptional<int32> MaximumParticipants);
        TSharedPtr<FEzSeasonModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);
        TSharedPtr<FEzSeasonModel> WithChallengePeriodEventId(const TOptional<FString> ChallengePeriodEventId);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int32> GetMaximumParticipants() const;
        FString GetMaximumParticipantsString() const;

        TOptional<FString> GetExperienceModelId() const;

        TOptional<FString> GetChallengePeriodEventId() const;

        Gs2::Matchmaking::Model::FSeasonModelPtr ToModel() const;
        static TSharedPtr<FEzSeasonModel> FromModel(Gs2::Matchmaking::Model::FSeasonModelPtr Model);
    };
    typedef TSharedPtr<FEzSeasonModel> FEzSeasonModelPtr;
}