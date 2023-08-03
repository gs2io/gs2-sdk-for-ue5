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

#include "EzGs2/Public/Experience/Model/Gs2ExperienceEzExperienceModel.h"

namespace Gs2::UE5::Experience::Model
{

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::WithDefaultExperience(
        const TOptional<int64> DefaultExperience
    )
    {
        this->DefaultExperienceValue = DefaultExperience;
        return SharedThis(this);
    }

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::WithDefaultRankCap(
        const TOptional<int64> DefaultRankCap
    )
    {
        this->DefaultRankCapValue = DefaultRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::WithMaxRankCap(
        const TOptional<int64> MaxRankCap
    )
    {
        this->MaxRankCapValue = MaxRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::WithRankThreshold(
        const TSharedPtr<Gs2::UE5::Experience::Model::FEzThreshold> RankThreshold
    )
    {
        this->RankThresholdValue = RankThreshold;
        return SharedThis(this);
    }

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::WithAcquireActionRates(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Experience::Model::FEzAcquireActionRate>>> AcquireActionRates
    )
    {
        this->AcquireActionRatesValue = AcquireActionRates;
        return SharedThis(this);
    }
    TOptional<FString> FEzExperienceModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzExperienceModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzExperienceModel::GetDefaultExperience() const
    {
        return DefaultExperienceValue;
    }

    FString FEzExperienceModel::GetDefaultExperienceString() const
    {
        if (!DefaultExperienceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue());
    }
    TOptional<int64> FEzExperienceModel::GetDefaultRankCap() const
    {
        return DefaultRankCapValue;
    }

    FString FEzExperienceModel::GetDefaultRankCapString() const
    {
        if (!DefaultRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue());
    }
    TOptional<int64> FEzExperienceModel::GetMaxRankCap() const
    {
        return MaxRankCapValue;
    }

    FString FEzExperienceModel::GetMaxRankCapString() const
    {
        if (!MaxRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue());
    }
    TSharedPtr<Gs2::UE5::Experience::Model::FEzThreshold> FEzExperienceModel::GetRankThreshold() const
    {
        return RankThresholdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Experience::Model::FEzAcquireActionRate>>> FEzExperienceModel::GetAcquireActionRates() const
    {
        return AcquireActionRatesValue;
    }

    Gs2::Experience::Model::FExperienceModelPtr FEzExperienceModel::ToModel() const
    {
        return MakeShared<Gs2::Experience::Model::FExperienceModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithDefaultExperience(DefaultExperienceValue)
            ->WithDefaultRankCap(DefaultRankCapValue)
            ->WithMaxRankCap(MaxRankCapValue)
            ->WithRankThreshold(RankThresholdValue == nullptr ? nullptr : RankThresholdValue->ToModel())
            ->WithAcquireActionRates([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Experience::Model::FAcquireActionRate>>>();
                    if (AcquireActionRatesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *AcquireActionRatesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzExperienceModel> FEzExperienceModel::FromModel(const Gs2::Experience::Model::FExperienceModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzExperienceModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithDefaultExperience(Model->GetDefaultExperience())
            ->WithDefaultRankCap(Model->GetDefaultRankCap())
            ->WithMaxRankCap(Model->GetMaxRankCap())
            ->WithRankThreshold(Model->GetRankThreshold() != nullptr ? Gs2::UE5::Experience::Model::FEzThreshold::FromModel(Model->GetRankThreshold()) : nullptr)
            ->WithAcquireActionRates([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireActionRate>>>();
                    if (Model->GetAcquireActionRates() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetAcquireActionRates())
                    {
                        v->Add(FEzAcquireActionRate::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}