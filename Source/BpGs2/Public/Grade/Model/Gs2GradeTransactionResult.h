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

#include "Grade/Model/Gs2GradeEzTransactionResult.h"
#include "Grade/Model/Gs2GradeVerifyActionResult.h"
#include "Grade/Model/Gs2GradeConsumeActionResult.h"
#include "Grade/Model/Gs2GradeAcquireActionResult.h"
#include "Gs2GradeTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2GradeTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2GradeVerifyActionResult> VerifyResults = TArray<FGs2GradeVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2GradeConsumeActionResult> ConsumeResults = TArray<FGs2GradeConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2GradeAcquireActionResult> AcquireResults = TArray<FGs2GradeAcquireActionResult>();
};

inline FGs2GradeTransactionResult EzTransactionResultToFGs2GradeTransactionResult(
    const Gs2::UE5::Grade::Model::FEzTransactionResultPtr Model
)
{
    FGs2GradeTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2GradeVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2GradeVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2GradeVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2GradeConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2GradeConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2GradeConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2GradeAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2GradeAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2GradeAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Grade::Model::FEzTransactionResultPtr FGs2GradeTransactionResultToEzTransactionResult(
    const FGs2GradeTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Grade::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Grade::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2GradeVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Grade::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2GradeConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Grade::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2GradeAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}