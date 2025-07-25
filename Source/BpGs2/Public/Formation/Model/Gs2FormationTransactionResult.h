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

#include "Formation/Model/Gs2FormationEzTransactionResult.h"
#include "Formation/Model/Gs2FormationVerifyActionResult.h"
#include "Formation/Model/Gs2FormationConsumeActionResult.h"
#include "Formation/Model/Gs2FormationAcquireActionResult.h"
#include "Gs2FormationTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2FormationTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2FormationVerifyActionResult> VerifyResults = TArray<FGs2FormationVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2FormationConsumeActionResult> ConsumeResults = TArray<FGs2FormationConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2FormationAcquireActionResult> AcquireResults = TArray<FGs2FormationAcquireActionResult>();
};

inline FGs2FormationTransactionResult EzTransactionResultToFGs2FormationTransactionResult(
    const Gs2::UE5::Formation::Model::FEzTransactionResultPtr Model
)
{
    FGs2FormationTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2FormationVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2FormationVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2FormationVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2FormationConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2FormationConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2FormationConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2FormationAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2FormationAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2FormationAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Formation::Model::FEzTransactionResultPtr FGs2FormationTransactionResultToEzTransactionResult(
    const FGs2FormationTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Formation::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Formation::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2FormationVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Formation::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2FormationConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Formation::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2FormationAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}