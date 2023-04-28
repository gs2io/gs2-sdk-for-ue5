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

#include "EzGs2/Public/Matchmaking/Model/Gs2MatchmakingEzBallot.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzBallot> FEzBallot::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBallot> FEzBallot::WithRatingName(
        const TOptional<FString> RatingName
    )
    {
        this->RatingNameValue = RatingName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBallot> FEzBallot::WithGatheringName(
        const TOptional<FString> GatheringName
    )
    {
        this->GatheringNameValue = GatheringName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBallot> FEzBallot::WithNumberOfPlayer(
        const TOptional<int32> NumberOfPlayer
    )
    {
        this->NumberOfPlayerValue = NumberOfPlayer;
        return SharedThis(this);
    }
    TOptional<FString> FEzBallot::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzBallot::GetRatingName() const
    {
        return RatingNameValue;
    }
    TOptional<FString> FEzBallot::GetGatheringName() const
    {
        return GatheringNameValue;
    }
    TOptional<int32> FEzBallot::GetNumberOfPlayer() const
    {
        return NumberOfPlayerValue;
    }

    FString FEzBallot::GetNumberOfPlayerString() const
    {
        if (!NumberOfPlayerValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NumberOfPlayerValue.GetValue());
    }

    Gs2::Matchmaking::Model::FBallotPtr FEzBallot::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FBallot>()
            ->WithUserId(UserIdValue)
            ->WithRatingName(RatingNameValue)
            ->WithGatheringName(GatheringNameValue)
            ->WithNumberOfPlayer(NumberOfPlayerValue);
    }

    TSharedPtr<FEzBallot> FEzBallot::FromModel(const Gs2::Matchmaking::Model::FBallotPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBallot>()
            ->WithUserId(Model->GetUserId())
            ->WithRatingName(Model->GetRatingName())
            ->WithGatheringName(Model->GetGatheringName())
            ->WithNumberOfPlayer(Model->GetNumberOfPlayer());
    }
}