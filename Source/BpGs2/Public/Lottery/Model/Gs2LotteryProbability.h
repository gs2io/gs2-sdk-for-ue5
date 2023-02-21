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

#include "Lottery/Model/Gs2LotteryEzProbability.h"
#include "Lottery/Model/Gs2LotteryDrawnPrize.h"
#include "Gs2LotteryProbability.generated.h"

USTRUCT(BlueprintType)
struct FGs2LotteryProbability
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FGs2LotteryDrawnPrize Prize = FGs2LotteryDrawnPrize();
    UPROPERTY(BlueprintReadWrite)
    float Rate = 0;
};

inline FGs2LotteryProbability EzProbabilityToFGs2LotteryProbability(
    const Gs2::UE5::Lottery::Model::FEzProbabilityPtr Model
)
{
    FGs2LotteryProbability Value;
    Value.Prize = Model->GetPrize() ? EzDrawnPrizeToFGs2LotteryDrawnPrize(Model->GetPrize()) : FGs2LotteryDrawnPrize();
    Value.Rate = Model->GetRate() ? *Model->GetRate() : 0;
    return Value;
}

inline Gs2::UE5::Lottery::Model::FEzProbabilityPtr FGs2LotteryProbabilityToEzProbability(
    const FGs2LotteryProbability Model
)
{
    return MakeShared<Gs2::UE5::Lottery::Model::FEzProbability>()
        ->WithPrize(FGs2LotteryDrawnPrizeToEzDrawnPrize(Model.Prize))
        ->WithRate(Model.Rate);
}