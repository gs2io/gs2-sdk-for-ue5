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
#include "Experience/Model/ExperienceModel.h"
#include "Gs2ExperienceEzThreshold.h"
#include "Gs2ExperienceEzAcquireActionRate.h"

namespace Gs2::UE5::Experience::Model
{
	class EZGS2_API FEzExperienceModel final : public TSharedFromThis<FEzExperienceModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> DefaultExperienceValue;
        TOptional<int64> DefaultRankCapValue;
        TOptional<int64> MaxRankCapValue;
        TSharedPtr<Gs2::UE5::Experience::Model::FEzThreshold> RankThresholdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Experience::Model::FEzAcquireActionRate>>> AcquireActionRatesValue;

	public:
        TSharedPtr<FEzExperienceModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzExperienceModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzExperienceModel> WithDefaultExperience(const TOptional<int64> DefaultExperience);
        TSharedPtr<FEzExperienceModel> WithDefaultRankCap(const TOptional<int64> DefaultRankCap);
        TSharedPtr<FEzExperienceModel> WithMaxRankCap(const TOptional<int64> MaxRankCap);
        TSharedPtr<FEzExperienceModel> WithRankThreshold(const TSharedPtr<Gs2::UE5::Experience::Model::FEzThreshold> RankThreshold);
        TSharedPtr<FEzExperienceModel> WithAcquireActionRates(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Experience::Model::FEzAcquireActionRate>>> AcquireActionRates);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetDefaultExperience() const;
        FString GetDefaultExperienceString() const;

        TOptional<int64> GetDefaultRankCap() const;
        FString GetDefaultRankCapString() const;

        TOptional<int64> GetMaxRankCap() const;
        FString GetMaxRankCapString() const;

        TSharedPtr<Gs2::UE5::Experience::Model::FEzThreshold> GetRankThreshold() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Experience::Model::FEzAcquireActionRate>>> GetAcquireActionRates() const;

        Gs2::Experience::Model::FExperienceModelPtr ToModel() const;
        static TSharedPtr<FEzExperienceModel> FromModel(Gs2::Experience::Model::FExperienceModelPtr Model);
    };
    typedef TSharedPtr<FEzExperienceModel> FEzExperienceModelPtr;
}