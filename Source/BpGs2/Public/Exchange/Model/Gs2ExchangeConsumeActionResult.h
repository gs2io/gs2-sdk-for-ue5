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

#include "Exchange/Model/Gs2ExchangeEzConsumeActionResult.h"
#include "Gs2ExchangeConsumeActionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeConsumeActionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ConsumeRequest = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 StatusCode = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString ConsumeResult = "";
};

inline FGs2ExchangeConsumeActionResult EzConsumeActionResultToFGs2ExchangeConsumeActionResult(
    const Gs2::UE5::Exchange::Model::FEzConsumeActionResultPtr Model
)
{
    FGs2ExchangeConsumeActionResult Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.ConsumeRequest = Model->GetConsumeRequest() ? *Model->GetConsumeRequest() : "";
    Value.StatusCode = Model->GetStatusCode() ? *Model->GetStatusCode() : 0;
    Value.ConsumeResult = Model->GetConsumeResult() ? *Model->GetConsumeResult() : "";
    return Value;
}

inline Gs2::UE5::Exchange::Model::FEzConsumeActionResultPtr FGs2ExchangeConsumeActionResultToEzConsumeActionResult(
    const FGs2ExchangeConsumeActionResult Model
)
{
    return MakeShared<Gs2::UE5::Exchange::Model::FEzConsumeActionResult>()
        ->WithAction(Model.Action)
        ->WithConsumeRequest(Model.ConsumeRequest)
        ->WithStatusCode(Model.StatusCode)
        ->WithConsumeResult(Model.ConsumeResult);
}