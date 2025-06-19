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

#include "Mission/Model/Gs2MissionEzTransactionResult.h"
#include "Mission/Model/Gs2MissionVerifyActionResult.h"
#include "Mission/Model/Gs2MissionConsumeActionResult.h"
#include "Mission/Model/Gs2MissionAcquireActionResult.h"
#include "Gs2MissionTransactionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2MissionTransactionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString TransactionId = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2MissionVerifyActionResult> VerifyResults = TArray<FGs2MissionVerifyActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2MissionConsumeActionResult> ConsumeResults = TArray<FGs2MissionConsumeActionResult>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2MissionAcquireActionResult> AcquireResults = TArray<FGs2MissionAcquireActionResult>();
};

inline FGs2MissionTransactionResult EzTransactionResultToFGs2MissionTransactionResult(
    const Gs2::UE5::Mission::Model::FEzTransactionResultPtr Model
)
{
    FGs2MissionTransactionResult Value;
    Value.TransactionId = Model->GetTransactionId() ? *Model->GetTransactionId() : "";
    Value.VerifyResults = Model->GetVerifyResults() ? [&]
    {
        TArray<FGs2MissionVerifyActionResult> r;
        for (auto v : *Model->GetVerifyResults())
        {r.Add(EzVerifyActionResultToFGs2MissionVerifyActionResult(v));
        }
        return r;
    }() : TArray<FGs2MissionVerifyActionResult>();
    Value.ConsumeResults = Model->GetConsumeResults() ? [&]
    {
        TArray<FGs2MissionConsumeActionResult> r;
        for (auto v : *Model->GetConsumeResults())
        {r.Add(EzConsumeActionResultToFGs2MissionConsumeActionResult(v));
        }
        return r;
    }() : TArray<FGs2MissionConsumeActionResult>();
    Value.AcquireResults = Model->GetAcquireResults() ? [&]
    {
        TArray<FGs2MissionAcquireActionResult> r;
        for (auto v : *Model->GetAcquireResults())
        {r.Add(EzAcquireActionResultToFGs2MissionAcquireActionResult(v));
        }
        return r;
    }() : TArray<FGs2MissionAcquireActionResult>();
    return Value;
}

inline Gs2::UE5::Mission::Model::FEzTransactionResultPtr FGs2MissionTransactionResultToEzTransactionResult(
    const FGs2MissionTransactionResult Model
)
{
    return MakeShared<Gs2::UE5::Mission::Model::FEzTransactionResult>()
        ->WithTransactionId(Model.TransactionId)
        ->WithVerifyResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Mission::Model::FEzVerifyActionResultPtr>>();
            for (auto v : Model.VerifyResults) {
                r->Add(FGs2MissionVerifyActionResultToEzVerifyActionResult(v));
            }
            return r;
        }())
        ->WithConsumeResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Mission::Model::FEzConsumeActionResultPtr>>();
            for (auto v : Model.ConsumeResults) {
                r->Add(FGs2MissionConsumeActionResultToEzConsumeActionResult(v));
            }
            return r;
        }())
        ->WithAcquireResults([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Mission::Model::FEzAcquireActionResultPtr>>();
            for (auto v : Model.AcquireResults) {
                r->Add(FGs2MissionAcquireActionResultToEzAcquireActionResult(v));
            }
            return r;
        }());
}