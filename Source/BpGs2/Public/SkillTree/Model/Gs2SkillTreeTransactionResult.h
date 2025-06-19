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

#include "SkillTree/Model/Gs2SkillTreeEzTransactionResult.h"
#include "SkillTree/Model/Gs2SkillTreeVerifyActionResult.h"
#include "SkillTree/Model/Gs2SkillTreeConsumeActionResult.h"
#include "SkillTree/Model/Gs2SkillTreeAcquireActionResult.h"
#include "Gs2SkillTreeTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2SkillTreeTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2SkillTreeVerifyActionResult> VerifyResults = TArray<FGs2SkillTreeVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2SkillTreeConsumeActionResult> ConsumeResults = TArray<FGs2SkillTreeConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2SkillTreeAcquireActionResult> AcquireResults = TArray<FGs2SkillTreeAcquireActionResult>();
};

inline FGs2SkillTreeTransactionResult EzTransactionResultToFGs2SkillTreeTransactionResult(
    const Gs2::UE5::SkillTree::Model::FEzTransactionResultPtr Model
)
{
    FGs2SkillTreeTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2SkillTreeVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2SkillTreeVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2SkillTreeVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2SkillTreeConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2SkillTreeConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2SkillTreeConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2SkillTreeAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2SkillTreeAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2SkillTreeAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::SkillTree::Model::FEzTransactionResultPtr FGs2SkillTreeTransactionResultToEzTransactionResult(
    const FGs2SkillTreeTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::SkillTree::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SkillTree::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2SkillTreeVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SkillTree::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2SkillTreeConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SkillTree::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2SkillTreeAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}