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

#include "Exchange/Model/Gs2ExchangeEzTransactionResult.h"
#include "Exchange/Model/Gs2ExchangeVerifyActionResult.h"
#include "Exchange/Model/Gs2ExchangeConsumeActionResult.h"
#include "Exchange/Model/Gs2ExchangeAcquireActionResult.h"
#include "Gs2ExchangeTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ExchangeVerifyActionResult> VerifyResults = TArray<FGs2ExchangeVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ExchangeConsumeActionResult> ConsumeResults = TArray<FGs2ExchangeConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ExchangeAcquireActionResult> AcquireResults = TArray<FGs2ExchangeAcquireActionResult>();
};

inline FGs2ExchangeTransactionResult EzTransactionResultToFGs2ExchangeTransactionResult(
    const Gs2::UE5::Exchange::Model::FEzTransactionResultPtr Model
)
{
    FGs2ExchangeTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2ExchangeVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2ExchangeVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2ExchangeVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2ExchangeConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2ExchangeConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2ExchangeConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2ExchangeAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2ExchangeAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2ExchangeAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Exchange::Model::FEzTransactionResultPtr FGs2ExchangeTransactionResultToEzTransactionResult(
    const FGs2ExchangeTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Exchange::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2ExchangeVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2ExchangeConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2ExchangeAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}