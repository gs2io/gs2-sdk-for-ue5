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

#include "Showcase/Model/Gs2ShowcaseEzTransactionResult.h"
#include "Showcase/Model/Gs2ShowcaseVerifyActionResult.h"
#include "Showcase/Model/Gs2ShowcaseConsumeActionResult.h"
#include "Showcase/Model/Gs2ShowcaseAcquireActionResult.h"
#include "Gs2ShowcaseTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ShowcaseVerifyActionResult> VerifyResults = TArray<FGs2ShowcaseVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ShowcaseConsumeActionResult> ConsumeResults = TArray<FGs2ShowcaseConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ShowcaseAcquireActionResult> AcquireResults = TArray<FGs2ShowcaseAcquireActionResult>();
};

inline FGs2ShowcaseTransactionResult EzTransactionResultToFGs2ShowcaseTransactionResult(
    const Gs2::UE5::Showcase::Model::FEzTransactionResultPtr Model
)
{
    FGs2ShowcaseTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2ShowcaseVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2ShowcaseVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2ShowcaseConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2ShowcaseConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2ShowcaseAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2ShowcaseAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Showcase::Model::FEzTransactionResultPtr FGs2ShowcaseTransactionResultToEzTransactionResult(
    const FGs2ShowcaseTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Showcase::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Showcase::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2ShowcaseVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Showcase::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2ShowcaseConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Showcase::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2ShowcaseAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}