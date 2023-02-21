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
#include "JobQueue/Domain/Model/Gs2JobQueueEzJobResultGameSessionDomain.h"
#include "Gs2JobQueueJobResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2JobQueueOwnJobResult
{
    GENERATED_BODY()

    Gs2::UE5::JobQueue::Domain::Model::FEzJobResultGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2JobQueueJobResultValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    int32 StatusCode = 0;
    UPROPERTY(BlueprintReadOnly)
    FString Result = "";
};

inline FGs2JobQueueJobResultValue EzJobResultToFGs2JobQueueJobResultValue(
    const Gs2::UE5::JobQueue::Model::FEzJobResultPtr Model
)
{
    FGs2JobQueueJobResultValue Value;
    Value.StatusCode = Model->GetStatusCode() ? *Model->GetStatusCode() : 0;
    Value.Result = Model->GetResult() ? *Model->GetResult() : "";
    return Value;
}

inline Gs2::UE5::JobQueue::Model::FEzJobResultPtr FGs2JobQueueJobResultValueToEzJobResult(
    const FGs2JobQueueJobResultValue Model
)
{
    return MakeShared<Gs2::UE5::JobQueue::Model::FEzJobResult>()
        ->WithStatusCode(Model.StatusCode)
        ->WithResult(Model.Result);
}

UCLASS()
class BPGS2_API UGs2JobQueueJobResultFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};