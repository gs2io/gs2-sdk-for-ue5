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

#include "Matchmaking/Model/Gs2MatchmakingEzSeasonModel.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithMaximumParticipants(
        const TOptional<int32> MaximumParticipants
    )
    {
        this->MaximumParticipantsValue = MaximumParticipants;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzSeasonModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSeasonModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzSeasonModel::GetMaximumParticipants() const
    {
        return MaximumParticipantsValue;
    }

    FString FEzSeasonModel::GetMaximumParticipantsString() const
    {
        if (!MaximumParticipantsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumParticipantsValue.GetValue());
    }
    TOptional<FString> FEzSeasonModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }
    TOptional<FString> FEzSeasonModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    Gs2::Matchmaking::Model::FSeasonModelPtr FEzSeasonModel::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FSeasonModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithMaximumParticipants(MaximumParticipantsValue)
            ->WithExperienceModelId(ExperienceModelIdValue)
            ->WithChallengePeriodEventId(ChallengePeriodEventIdValue);
    }

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::FromModel(const Gs2::Matchmaking::Model::FSeasonModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSeasonModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithMaximumParticipants(Model->GetMaximumParticipants())
            ->WithExperienceModelId(Model->GetExperienceModelId())
            ->WithChallengePeriodEventId(Model->GetChallengePeriodEventId());
    }
}