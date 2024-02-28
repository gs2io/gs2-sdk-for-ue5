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
#include "SeasonRating/Model/SeasonModel.h"
#include "Gs2SeasonRatingEzTierModel.h"

namespace Gs2::UE5::SeasonRating::Model
{
	class EZGS2_API FEzSeasonModel final : public TSharedFromThis<FEzSeasonModel>
	{
        TOptional<FString> SeasonModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzTierModel>>> TiersValue;
        TOptional<FString> ExperienceModelIdValue;

	public:
        TSharedPtr<FEzSeasonModel> WithSeasonModelId(const TOptional<FString> SeasonModelId);
        TSharedPtr<FEzSeasonModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzSeasonModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSeasonModel> WithTiers(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzTierModel>>> Tiers);
        TSharedPtr<FEzSeasonModel> WithExperienceModelId(const TOptional<FString> ExperienceModelId);

        TOptional<FString> GetSeasonModelId() const;

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzTierModel>>> GetTiers() const;

        TOptional<FString> GetExperienceModelId() const;

        Gs2::SeasonRating::Model::FSeasonModelPtr ToModel() const;
        static TSharedPtr<FEzSeasonModel> FromModel(Gs2::SeasonRating::Model::FSeasonModelPtr Model);
    };
    typedef TSharedPtr<FEzSeasonModel> FEzSeasonModelPtr;
}