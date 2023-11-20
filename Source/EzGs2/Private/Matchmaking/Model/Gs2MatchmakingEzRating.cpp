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

#include "Matchmaking/Model/Gs2MatchmakingEzRating.h"

namespace Gs2::UE5::Matchmaking::Model
{

    TSharedPtr<FEzRating> FEzRating::WithRatingId(
        const TOptional<FString> RatingId
    )
    {
        this->RatingIdValue = RatingId;
        return SharedThis(this);
    }

    TSharedPtr<FEzRating> FEzRating::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzRating> FEzRating::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzRating> FEzRating::WithRateValue(
        const TOptional<float> RateValue
    )
    {
        this->RateValueValue = RateValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzRating> FEzRating::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FEzRating> FEzRating::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzRating::GetRatingId() const
    {
        return RatingIdValue;
    }
    TOptional<FString> FEzRating::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzRating::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<float> FEzRating::GetRateValue() const
    {
        return RateValueValue;
    }

    FString FEzRating::GetRateValueString() const
    {
        if (!RateValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValueValue.GetValue());
    }
    TOptional<int64> FEzRating::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzRating::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FEzRating::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzRating::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Matchmaking::Model::FRatingPtr FEzRating::ToModel() const
    {
        return MakeShared<Gs2::Matchmaking::Model::FRating>()
            ->WithRatingId(RatingIdValue)
            ->WithName(NameValue)
            ->WithUserId(UserIdValue)
            ->WithRateValue(RateValueValue)
            ->WithCreatedAt(CreatedAtValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzRating> FEzRating::FromModel(const Gs2::Matchmaking::Model::FRatingPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzRating>()
            ->WithRatingId(Model->GetRatingId())
            ->WithName(Model->GetName())
            ->WithUserId(Model->GetUserId())
            ->WithRateValue(Model->GetRateValue())
            ->WithCreatedAt(Model->GetCreatedAt())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}