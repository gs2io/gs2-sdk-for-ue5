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

#include "Experience/Model/Gs2ExperienceEzTransactionResult.h"
#include "Experience/Model/Gs2ExperienceVerifyActionResult.h"
#include "Experience/Model/Gs2ExperienceConsumeActionResult.h"
#include "Experience/Model/Gs2ExperienceAcquireActionResult.h"
#include "Gs2ExperienceTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExperienceTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2CoreVerifyActionResult> VerifyResults = TArray<FGs2CoreVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2CoreConsumeActionResult> ConsumeResults = TArray<FGs2CoreConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2CoreAcquireActionResult> AcquireResults = TArray<FGs2CoreAcquireActionResult>();
};

inline FGs2ExperienceTransactionResult EzTransactionResultToFGs2ExperienceTransactionResult(
    const Gs2::UE5::Experience::Model::FEzTransactionResultPtr Model
)
{
    FGs2ExperienceTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2CoreVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2ExperienceVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2CoreVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2CoreConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2ExperienceConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2CoreConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2CoreAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2ExperienceAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2CoreAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Experience::Model::FEzTransactionResultPtr FGs2ExperienceTransactionResultToEzTransactionResult(
    const FGs2ExperienceTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Experience::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Experience::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2ExperienceVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Experience::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2ExperienceConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Experience::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2ExperienceAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}