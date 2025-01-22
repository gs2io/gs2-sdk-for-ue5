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

#include "Quest/Model/Gs2QuestEzVerifyActionResult.h"
#include "Gs2QuestVerifyActionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2QuestVerifyActionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString VerifyRequest = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 StatusCode = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString VerifyResult = "";
};

inline FGs2QuestVerifyActionResult EzVerifyActionResultToFGs2QuestVerifyActionResult(
    const Gs2::UE5::Quest::Model::FEzVerifyActionResultPtr Model
)
{
    FGs2QuestVerifyActionResult Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.VerifyRequest = Model->GetVerifyRequest() ? *Model->GetVerifyRequest() : "";
    Value.StatusCode = Model->GetStatusCode() ? *Model->GetStatusCode() : 0;
    Value.VerifyResult = Model->GetVerifyResult() ? *Model->GetVerifyResult() : "";
    return Value;
}

inline Gs2::UE5::Quest::Model::FEzVerifyActionResultPtr FGs2QuestVerifyActionResultToEzVerifyActionResult(
    const FGs2QuestVerifyActionResult Model
)
{
    return MakeShared<Gs2::UE5::Quest::Model::FEzVerifyActionResult>()
        ->WithAction(Model.Action)
        ->WithVerifyRequest(Model.VerifyRequest)
        ->WithStatusCode(Model.StatusCode)
        ->WithVerifyResult(Model.VerifyResult);
}