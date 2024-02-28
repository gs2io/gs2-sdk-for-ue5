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

#include "SeasonRating/Model/Gs2SeasonRatingEzSeasonModel.h"

namespace Gs2::UE5::SeasonRating::Model
{

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithSeasonModelId(
        const TOptional<FString> SeasonModelId
    )
    {
        this->SeasonModelIdValue = SeasonModelId;
        return SharedThis(this);
    }

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

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithTiers(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzTierModel>>> Tiers
    )
    {
        this->TiersValue = Tiers;
        return SharedThis(this);
    }

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }
    TOptional<FString> FEzSeasonModel::GetSeasonModelId() const
    {
        return SeasonModelIdValue;
    }
    TOptional<FString> FEzSeasonModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzSeasonModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SeasonRating::Model::FEzTierModel>>> FEzSeasonModel::GetTiers() const
    {
        return TiersValue;
    }
    TOptional<FString> FEzSeasonModel::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }

    Gs2::SeasonRating::Model::FSeasonModelPtr FEzSeasonModel::ToModel() const
    {
        return MakeShared<Gs2::SeasonRating::Model::FSeasonModel>()
            ->WithSeasonModelId(SeasonModelIdValue)
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithTiers([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::SeasonRating::Model::FTierModel>>>();
                    if (TiersValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *TiersValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithExperienceModelId(ExperienceModelIdValue);
    }

    TSharedPtr<FEzSeasonModel> FEzSeasonModel::FromModel(const Gs2::SeasonRating::Model::FSeasonModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSeasonModel>()
            ->WithSeasonModelId(Model->GetSeasonModelId())
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithTiers([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzTierModel>>>();
                    if (Model->GetTiers() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetTiers())
                    {
                        v->Add(FEzTierModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithExperienceModelId(Model->GetExperienceModelId());
    }
}