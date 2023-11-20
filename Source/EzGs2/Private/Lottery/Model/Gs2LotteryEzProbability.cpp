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

#include "Lottery/Model/Gs2LotteryEzProbability.h"

namespace Gs2::UE5::Lottery::Model
{

    TSharedPtr<FEzProbability> FEzProbability::WithPrize(
        const TSharedPtr<Gs2::UE5::Lottery::Model::FEzDrawnPrize> Prize
    )
    {
        this->PrizeValue = Prize;
        return SharedThis(this);
    }

    TSharedPtr<FEzProbability> FEzProbability::WithRate(
        const TOptional<float> Rate
    )
    {
        this->RateValue = Rate;
        return SharedThis(this);
    }
    TSharedPtr<Gs2::UE5::Lottery::Model::FEzDrawnPrize> FEzProbability::GetPrize() const
    {
        return PrizeValue;
    }
    TOptional<float> FEzProbability::GetRate() const
    {
        return RateValue;
    }

    FString FEzProbability::GetRateString() const
    {
        if (!RateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RateValue.GetValue());
    }

    Gs2::Lottery::Model::FProbabilityPtr FEzProbability::ToModel() const
    {
        return MakeShared<Gs2::Lottery::Model::FProbability>()
            ->WithPrize(PrizeValue == nullptr ? nullptr : PrizeValue->ToModel())
            ->WithRate(RateValue);
    }

    TSharedPtr<FEzProbability> FEzProbability::FromModel(const Gs2::Lottery::Model::FProbabilityPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzProbability>()
            ->WithPrize(Model->GetPrize() != nullptr ? Gs2::UE5::Lottery::Model::FEzDrawnPrize::FromModel(Model->GetPrize()) : nullptr)
            ->WithRate(Model->GetRate());
    }
}