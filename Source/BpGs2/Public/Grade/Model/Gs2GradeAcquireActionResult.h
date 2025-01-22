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

#include "Grade/Model/Gs2GradeEzAcquireActionResult.h"
#include "Gs2GradeAcquireActionResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2GradeAcquireActionResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString AcquireRequest = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 StatusCode = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString AcquireResult = "";
};

inline FGs2GradeAcquireActionResult EzAcquireActionResultToFGs2GradeAcquireActionResult(
    const Gs2::UE5::Grade::Model::FEzAcquireActionResultPtr Model
)
{
    FGs2GradeAcquireActionResult Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.AcquireRequest = Model->GetAcquireRequest() ? *Model->GetAcquireRequest() : "";
    Value.StatusCode = Model->GetStatusCode() ? *Model->GetStatusCode() : 0;
    Value.AcquireResult = Model->GetAcquireResult() ? *Model->GetAcquireResult() : "";
    return Value;
}

inline Gs2::UE5::Grade::Model::FEzAcquireActionResultPtr FGs2GradeAcquireActionResultToEzAcquireActionResult(
    const FGs2GradeAcquireActionResult Model
)
{
    return MakeShared<Gs2::UE5::Grade::Model::FEzAcquireActionResult>()
        ->WithAction(Model.Action)
        ->WithAcquireRequest(Model.AcquireRequest)
        ->WithStatusCode(Model.StatusCode)
        ->WithAcquireResult(Model.AcquireResult);
}