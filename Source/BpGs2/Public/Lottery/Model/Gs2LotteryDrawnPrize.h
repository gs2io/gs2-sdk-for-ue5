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

#include "Lottery/Model/Gs2LotteryEzDrawnPrize.h"
#include "Lottery/Model/Gs2LotteryAcquireAction.h"
#include "Gs2LotteryDrawnPrize.generated.h"

USTRUCT(BlueprintType)
struct FGs2LotteryDrawnPrize
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString PrizeId = "";
    UPROPERTY(BlueprintReadWrite)
    TArray<FGs2LotteryAcquireAction> AcquireActions = TArray<FGs2LotteryAcquireAction>();
};

inline FGs2LotteryDrawnPrize EzDrawnPrizeToFGs2LotteryDrawnPrize(
    const Gs2::UE5::Lottery::Model::FEzDrawnPrizePtr Model
)
{
    FGs2LotteryDrawnPrize Value;
    Value.PrizeId = Model->GetPrizeId() ? *Model->GetPrizeId() : "";
    Value.AcquireActions = Model->GetAcquireActions() ? [&]
    {
        TArray<FGs2LotteryAcquireAction> r;
        for (auto v : *Model->GetAcquireActions())
        {r.Add(EzAcquireActionToFGs2LotteryAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2LotteryAcquireAction>();
    return Value;
}

inline Gs2::UE5::Lottery::Model::FEzDrawnPrizePtr FGs2LotteryDrawnPrizeToEzDrawnPrize(
    const FGs2LotteryDrawnPrize Model
)
{
    return MakeShared<Gs2::UE5::Lottery::Model::FEzDrawnPrize>()
        ->WithPrizeId(Model.PrizeId)
        ->WithAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Lottery::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.AcquireActions) {
                r->Add(FGs2LotteryAcquireActionToEzAcquireAction(v));
            }
            return r;
        }());
}