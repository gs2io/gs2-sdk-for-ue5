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
#include "Matchmaking/Model/RatingModel.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzRatingModel final : public TSharedFromThis<FEzRatingModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> VolatilityValue;

	public:
        TSharedPtr<FEzRatingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzRatingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzRatingModel> WithVolatility(const TOptional<int32> Volatility);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int32> GetVolatility() const;
        FString GetVolatilityString() const;

        Gs2::Matchmaking::Model::FRatingModelPtr ToModel() const;
        static TSharedPtr<FEzRatingModel> FromModel(Gs2::Matchmaking::Model::FRatingModelPtr Model);
    };
    typedef TSharedPtr<FEzRatingModel> FEzRatingModelPtr;
}