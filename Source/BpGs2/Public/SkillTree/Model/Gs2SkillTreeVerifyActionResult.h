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

#include "SkillTree/Model/Gs2SkillTreeEzVerifyActionResult.h"
#include "Gs2SkillTreeVerifyActionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2SkillTreeVerifyActionResult
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

inline FGs2SkillTreeVerifyActionResult EzVerifyActionResultToFGs2SkillTreeVerifyActionResult(
    const Gs2::UE5::SkillTree::Model::FEzVerifyActionResultPtr Model
)
{
    FGs2SkillTreeVerifyActionResult Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.VerifyRequest = Model->GetVerifyRequest() ? *Model->GetVerifyRequest() : "";
    Value.StatusCode = Model->GetStatusCode() ? *Model->GetStatusCode() : 0;
    Value.VerifyResult = Model->GetVerifyResult() ? *Model->GetVerifyResult() : "";
    return Value;
}

inline Gs2::UE5::SkillTree::Model::FEzVerifyActionResultPtr FGs2SkillTreeVerifyActionResultToEzVerifyActionResult(
    const FGs2SkillTreeVerifyActionResult Model
)
{
    return MakeShared<Gs2::UE5::SkillTree::Model::FEzVerifyActionResult>()
        ->WithAction(Model.Action)
        ->WithVerifyRequest(Model.VerifyRequest)
        ->WithStatusCode(Model.StatusCode)
        ->WithVerifyResult(Model.VerifyResult);
}