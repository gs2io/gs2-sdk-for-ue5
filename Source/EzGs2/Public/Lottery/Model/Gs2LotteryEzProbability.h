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
#include "Lottery/Model/Probability.h"
#include "Gs2LotteryEzDrawnPrize.h"

namespace Gs2::UE5::Lottery::Model
{
	class EZGS2_API FEzProbability final : public TSharedFromThis<FEzProbability>
	{
        TSharedPtr<Gs2::UE5::Lottery::Model::FEzDrawnPrize> PrizeValue;
        TOptional<float> RateValue;

	public:
        TSharedPtr<FEzProbability> WithPrize(const TSharedPtr<Gs2::UE5::Lottery::Model::FEzDrawnPrize> Prize);
        TSharedPtr<FEzProbability> WithRate(const TOptional<float> Rate);

        TSharedPtr<Gs2::UE5::Lottery::Model::FEzDrawnPrize> GetPrize() const;

        TOptional<float> GetRate() const;
        FString GetRateString() const;

        Gs2::Lottery::Model::FProbabilityPtr ToModel() const;
        static TSharedPtr<FEzProbability> FromModel(Gs2::Lottery::Model::FProbabilityPtr Model);
    };
    typedef TSharedPtr<FEzProbability> FEzProbabilityPtr;
}