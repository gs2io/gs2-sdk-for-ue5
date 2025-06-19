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

#include "Lottery/Model/Gs2LotteryEzTransactionResult.h"
#include "Lottery/Model/Gs2LotteryVerifyActionResult.h"
#include "Lottery/Model/Gs2LotteryConsumeActionResult.h"
#include "Lottery/Model/Gs2LotteryAcquireActionResult.h"
#include "Gs2LotteryTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2LotteryTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2LotteryVerifyActionResult> VerifyResults = TArray<FGs2LotteryVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2LotteryConsumeActionResult> ConsumeResults = TArray<FGs2LotteryConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2LotteryAcquireActionResult> AcquireResults = TArray<FGs2LotteryAcquireActionResult>();
};

inline FGs2LotteryTransactionResult EzTransactionResultToFGs2LotteryTransactionResult(
    const Gs2::UE5::Lottery::Model::FEzTransactionResultPtr Model
)
{
    FGs2LotteryTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2LotteryVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2LotteryVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2LotteryVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2LotteryConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2LotteryConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2LotteryConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2LotteryAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2LotteryAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2LotteryAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Lottery::Model::FEzTransactionResultPtr FGs2LotteryTransactionResultToEzTransactionResult(
    const FGs2LotteryTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Lottery::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Lottery::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2LotteryVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Lottery::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2LotteryConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Lottery::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2LotteryAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}