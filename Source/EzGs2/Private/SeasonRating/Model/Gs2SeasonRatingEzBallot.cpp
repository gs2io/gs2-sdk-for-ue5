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

#include "SeasonRating/Model/Gs2SeasonRatingEzBallot.h"

namespace Gs2::UE5::SeasonRating::Model
{

    TSharedPtr<FEzBallot> FEzBallot::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzBallot> FEzBallot::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FEzBallot> FEzBallot::WithSessionName(
        const TOptional<FString> SessionName
    )
    {
        this->SessionNameValue = SessionName;
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
    TOptional<FString> FEzBallot::GetSeasonName() const
    {
        return SeasonNameValue;
    }
    TOptional<FString> FEzBallot::GetSessionName() const
    {
        return SessionNameValue;
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

    Gs2::SeasonRating::Model::FBallotPtr FEzBallot::ToModel() const
    {
        return MakeShared<Gs2::SeasonRating::Model::FBallot>()
            ->WithUserId(UserIdValue)
            ->WithSeasonName(SeasonNameValue)
            ->WithSessionName(SessionNameValue)
            ->WithNumberOfPlayer(NumberOfPlayerValue);
    }

    TSharedPtr<FEzBallot> FEzBallot::FromModel(const Gs2::SeasonRating::Model::FBallotPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzBallot>()
            ->WithUserId(Model->GetUserId())
            ->WithSeasonName(Model->GetSeasonName())
            ->WithSessionName(Model->GetSessionName())
            ->WithNumberOfPlayer(Model->GetNumberOfPlayer());
    }
}