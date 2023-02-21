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
#include "JobQueue/Domain/Model/Gs2JobQueueEzJobGameSessionDomain.h"
#include "Gs2JobQueueJob.generated.h"

USTRUCT(BlueprintType)
struct FGs2JobQueueOwnJob
{
    GENERATED_BODY()

    Gs2::UE5::JobQueue::Domain::Model::FEzJobGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2JobQueueJobValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString JobId = "";
    UPROPERTY(BlueprintReadOnly)
    FString ScriptId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Args = "";
    UPROPERTY(BlueprintReadOnly)
    int32 CurrentRetryCount = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 MaxTryCount = 0;
};

inline FGs2JobQueueJobValue EzJobToFGs2JobQueueJobValue(
    const Gs2::UE5::JobQueue::Model::FEzJobPtr Model
)
{
    FGs2JobQueueJobValue Value;
    Value.JobId = Model->GetJobId() ? *Model->GetJobId() : "";
    Value.ScriptId = Model->GetScriptId() ? *Model->GetScriptId() : "";
    Value.Args = Model->GetArgs() ? *Model->GetArgs() : "";
    Value.CurrentRetryCount = Model->GetCurrentRetryCount() ? *Model->GetCurrentRetryCount() : 0;
    Value.MaxTryCount = Model->GetMaxTryCount() ? *Model->GetMaxTryCount() : 0;
    return Value;
}

inline Gs2::UE5::JobQueue::Model::FEzJobPtr FGs2JobQueueJobValueToEzJob(
    const FGs2JobQueueJobValue Model
)
{
    return MakeShared<Gs2::UE5::JobQueue::Model::FEzJob>()
        ->WithJobId(Model.JobId)
        ->WithScriptId(Model.ScriptId)
        ->WithArgs(Model.Args)
        ->WithCurrentRetryCount(Model.CurrentRetryCount)
        ->WithMaxTryCount(Model.MaxTryCount);
}

UCLASS()
class BPGS2_API UGs2JobQueueJobFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::JobQueue::OwnJobResult", Category="Game Server Services|GS2-JobQueue|Namespace|User|Job|JobResult", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="JobResult") FGs2JobQueueOwnJobResult OwnJobResult(
        FGs2JobQueueOwnJob Job,
        int32 TryNumber
    );
};