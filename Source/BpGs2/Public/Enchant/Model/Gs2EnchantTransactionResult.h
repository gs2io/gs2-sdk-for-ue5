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

#include "Enchant/Model/Gs2EnchantEzTransactionResult.h"
#include "Enchant/Model/Gs2EnchantVerifyActionResult.h"
#include "Enchant/Model/Gs2EnchantConsumeActionResult.h"
#include "Enchant/Model/Gs2EnchantAcquireActionResult.h"
#include "Gs2EnchantTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnchantVerifyActionResult> VerifyResults = TArray<FGs2EnchantVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnchantConsumeActionResult> ConsumeResults = TArray<FGs2EnchantConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnchantAcquireActionResult> AcquireResults = TArray<FGs2EnchantAcquireActionResult>();
};

inline FGs2EnchantTransactionResult EzTransactionResultToFGs2EnchantTransactionResult(
    const Gs2::UE5::Enchant::Model::FEzTransactionResultPtr Model
)
{
    FGs2EnchantTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2EnchantVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2EnchantVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2EnchantVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2EnchantConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2EnchantConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2EnchantConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2EnchantAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2EnchantAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2EnchantAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzTransactionResultPtr FGs2EnchantTransactionResultToEzTransactionResult(
    const FGs2EnchantTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2EnchantVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2EnchantConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2EnchantAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}