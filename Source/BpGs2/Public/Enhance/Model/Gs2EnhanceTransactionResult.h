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

#include "Enhance/Model/Gs2EnhanceEzTransactionResult.h"
#include "Enhance/Model/Gs2EnhanceVerifyActionResult.h"
#include "Enhance/Model/Gs2EnhanceConsumeActionResult.h"
#include "Enhance/Model/Gs2EnhanceAcquireActionResult.h"
#include "Gs2EnhanceTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnhanceVerifyActionResult> VerifyResults = TArray<FGs2EnhanceVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnhanceConsumeActionResult> ConsumeResults = TArray<FGs2EnhanceConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2EnhanceAcquireActionResult> AcquireResults = TArray<FGs2EnhanceAcquireActionResult>();
};

inline FGs2EnhanceTransactionResult EzTransactionResultToFGs2EnhanceTransactionResult(
    const Gs2::UE5::Enhance::Model::FEzTransactionResultPtr Model
)
{
    FGs2EnhanceTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2EnhanceVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2EnhanceVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2EnhanceVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2EnhanceConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2EnhanceConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2EnhanceConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2EnhanceAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2EnhanceAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2EnhanceAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzTransactionResultPtr FGs2EnhanceTransactionResultToEzTransactionResult(
    const FGs2EnhanceTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enhance::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2EnhanceVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enhance::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2EnhanceConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enhance::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2EnhanceAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}