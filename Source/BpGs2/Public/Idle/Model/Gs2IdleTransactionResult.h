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

#include "Idle/Model/Gs2IdleEzTransactionResult.h"
#include "Idle/Model/Gs2IdleVerifyActionResult.h"
#include "Idle/Model/Gs2IdleConsumeActionResult.h"
#include "Idle/Model/Gs2IdleAcquireActionResult.h"
#include "Gs2IdleTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2IdleTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2IdleVerifyActionResult> VerifyResults = TArray<FGs2IdleVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2IdleConsumeActionResult> ConsumeResults = TArray<FGs2IdleConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2IdleAcquireActionResult> AcquireResults = TArray<FGs2IdleAcquireActionResult>();
};

inline FGs2IdleTransactionResult EzTransactionResultToFGs2IdleTransactionResult(
    const Gs2::UE5::Idle::Model::FEzTransactionResultPtr Model
)
{
    FGs2IdleTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2IdleVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2IdleVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2IdleVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2IdleConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2IdleConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2IdleConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2IdleAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2IdleAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2IdleAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Idle::Model::FEzTransactionResultPtr FGs2IdleTransactionResultToEzTransactionResult(
    const FGs2IdleTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Idle::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Idle::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2IdleVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Idle::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2IdleConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Idle::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2IdleAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}