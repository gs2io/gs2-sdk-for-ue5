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

#include "Quest/Model/Gs2QuestEzTransactionResult.h"
#include "Quest/Model/Gs2QuestVerifyActionResult.h"
#include "Quest/Model/Gs2QuestConsumeActionResult.h"
#include "Quest/Model/Gs2QuestAcquireActionResult.h"
#include "Gs2QuestTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2QuestVerifyActionResult> VerifyResults = TArray<FGs2QuestVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2QuestConsumeActionResult> ConsumeResults = TArray<FGs2QuestConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2QuestAcquireActionResult> AcquireResults = TArray<FGs2QuestAcquireActionResult>();
};

inline FGs2QuestTransactionResult EzTransactionResultToFGs2QuestTransactionResult(
    const Gs2::UE5::Quest::Model::FEzTransactionResultPtr Model
)
{
    FGs2QuestTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2QuestVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2QuestVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2QuestVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2QuestConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2QuestConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2QuestConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2QuestAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2QuestAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2QuestAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzTransactionResultPtr FGs2QuestTransactionResultToEzTransactionResult(
    const FGs2QuestTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2QuestVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2QuestConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Quest::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2QuestAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}