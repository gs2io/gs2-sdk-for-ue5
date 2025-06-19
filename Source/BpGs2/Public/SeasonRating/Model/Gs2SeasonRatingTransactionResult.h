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

#include "SeasonRating/Model/Gs2SeasonRatingEzTransactionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingVerifyActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingConsumeActionResult.h"
#include "SeasonRating/Model/Gs2SeasonRatingAcquireActionResult.h"
#include "Gs2SeasonRatingTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2SeasonRatingTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2SeasonRatingVerifyActionResult> VerifyResults = TArray<FGs2SeasonRatingVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2SeasonRatingConsumeActionResult> ConsumeResults = TArray<FGs2SeasonRatingConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2SeasonRatingAcquireActionResult> AcquireResults = TArray<FGs2SeasonRatingAcquireActionResult>();
};

inline FGs2SeasonRatingTransactionResult EzTransactionResultToFGs2SeasonRatingTransactionResult(
    const Gs2::UE5::SeasonRating::Model::FEzTransactionResultPtr Model
)
{
    FGs2SeasonRatingTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2SeasonRatingVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2SeasonRatingVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2SeasonRatingVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2SeasonRatingConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2SeasonRatingConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2SeasonRatingConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2SeasonRatingAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2SeasonRatingAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2SeasonRatingAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::SeasonRating::Model::FEzTransactionResultPtr FGs2SeasonRatingTransactionResultToEzTransactionResult(
    const FGs2SeasonRatingTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::SeasonRating::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SeasonRating::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2SeasonRatingVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SeasonRating::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2SeasonRatingConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SeasonRating::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2SeasonRatingAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}