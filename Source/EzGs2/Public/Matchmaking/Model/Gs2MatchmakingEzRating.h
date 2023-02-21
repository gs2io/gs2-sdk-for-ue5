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
#include "Matchmaking/Model/Rating.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzRating final : public TSharedFromThis<FEzRating>
	{
        TOptional<FString> RatingIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> UserIdValue;
        TOptional<float> RateValueValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzRating> WithRatingId(const TOptional<FString> RatingId);
        TSharedPtr<FEzRating> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRating> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzRating> WithRateValue(const TOptional<float> RateValue);
        TSharedPtr<FEzRating> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEzRating> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetRatingId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetUserId() const;

        TOptional<float> GetRateValue() const;
        FString GetRateValueString() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Matchmaking::Model::FRatingPtr ToModel() const;
        static TSharedPtr<FEzRating> FromModel(Gs2::Matchmaking::Model::FRatingPtr Model);
    };
    typedef TSharedPtr<FEzRating> FEzRatingPtr;
}