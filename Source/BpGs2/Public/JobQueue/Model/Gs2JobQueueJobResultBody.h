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

#include "JobQueue/Model/Gs2JobQueueEzJobResultBody.h"
#include "Gs2JobQueueJobResultBody.generated.h"

USTRUCT(BlueprintType)
struct FGs2JobQueueJobResultBody
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 TryNumber = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 StatusCode = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Result = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int64 TryAt = 0;
};

inline FGs2JobQueueJobResultBody EzJobResultBodyToFGs2JobQueueJobResultBody(
    const Gs2::UE5::JobQueue::Model::FEzJobResultBodyPtr Model
)
{
    FGs2JobQueueJobResultBody Value;
    Value.TryNumber = Model->GetTryNumber() ? *Model->GetTryNumber() : 0;
    Value.StatusCode = Model->GetStatusCode() ? *Model->GetStatusCode() : 0;
    Value.Result = Model->GetResult() ? *Model->GetResult() : "";
    Value.TryAt = Model->GetTryAt() ? *Model->GetTryAt() : 0;
    return Value;
}

inline Gs2::UE5::JobQueue::Model::FEzJobResultBodyPtr FGs2JobQueueJobResultBodyToEzJobResultBody(
    const FGs2JobQueueJobResultBody Model
)
{
    return MakeShared<Gs2::UE5::JobQueue::Model::FEzJobResultBody>()
        ->WithTryNumber(Model.TryNumber)
        ->WithStatusCode(Model.StatusCode)
        ->WithResult(Model.Result)
        ->WithTryAt(Model.TryAt);
}