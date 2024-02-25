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

#include "SeasonRating/Model/Gs2SeasonRatingEzTierModel.h"

namespace Gs2::UE5::SeasonRating::Model
{

    TSharedPtr<FEzTierModel> FEzTierModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzTierModel> FEzTierModel::WithRaiseRankBonus(
        const TOptional<int32> RaiseRankBonus
    )
    {
        this->RaiseRankBonusValue = RaiseRankBonus;
        return SharedThis(this);
    }

    TSharedPtr<FEzTierModel> FEzTierModel::WithMinimumChangePoint(
        const TOptional<int32> MinimumChangePoint
    )
    {
        this->MinimumChangePointValue = MinimumChangePoint;
        return SharedThis(this);
    }

    TSharedPtr<FEzTierModel> FEzTierModel::WithMaximumChangePoint(
        const TOptional<int32> MaximumChangePoint
    )
    {
        this->MaximumChangePointValue = MaximumChangePoint;
        return SharedThis(this);
    }
    TOptional<FString> FEzTierModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FEzTierModel::GetRaiseRankBonus() const
    {
        return RaiseRankBonusValue;
    }

    FString FEzTierModel::GetRaiseRankBonusString() const
    {
        if (!RaiseRankBonusValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RaiseRankBonusValue.GetValue());
    }
    TOptional<int32> FEzTierModel::GetMinimumChangePoint() const
    {
        return MinimumChangePointValue;
    }

    FString FEzTierModel::GetMinimumChangePointString() const
    {
        if (!MinimumChangePointValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MinimumChangePointValue.GetValue());
    }
    TOptional<int32> FEzTierModel::GetMaximumChangePoint() const
    {
        return MaximumChangePointValue;
    }

    FString FEzTierModel::GetMaximumChangePointString() const
    {
        if (!MaximumChangePointValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumChangePointValue.GetValue());
    }

    Gs2::SeasonRating::Model::FTierModelPtr FEzTierModel::ToModel() const
    {
        return MakeShared<Gs2::SeasonRating::Model::FTierModel>()
            ->WithMetadata(MetadataValue)
            ->WithRaiseRankBonus(RaiseRankBonusValue)
            ->WithMinimumChangePoint(MinimumChangePointValue)
            ->WithMaximumChangePoint(MaximumChangePointValue);
    }

    TSharedPtr<FEzTierModel> FEzTierModel::FromModel(const Gs2::SeasonRating::Model::FTierModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzTierModel>()
            ->WithMetadata(Model->GetMetadata())
            ->WithRaiseRankBonus(Model->GetRaiseRankBonus())
            ->WithMinimumChangePoint(Model->GetMinimumChangePoint())
            ->WithMaximumChangePoint(Model->GetMaximumChangePoint());
    }
}