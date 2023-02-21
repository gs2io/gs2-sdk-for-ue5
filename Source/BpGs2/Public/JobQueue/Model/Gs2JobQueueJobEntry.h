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

#include "JobQueue/Model/Gs2JobQueueEzJobEntry.h"
#include "Gs2JobQueueJobEntry.generated.h"

USTRUCT(BlueprintType)
struct FGs2JobQueueJobEntry
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString ScriptId = "";
    UPROPERTY(BlueprintReadWrite)
    FString Args = "";
    UPROPERTY(BlueprintReadWrite)
    int32 MaxTryCount = 0;
};

inline FGs2JobQueueJobEntry EzJobEntryToFGs2JobQueueJobEntry(
    const Gs2::UE5::JobQueue::Model::FEzJobEntryPtr Model
)
{
    FGs2JobQueueJobEntry Value;
    Value.ScriptId = Model->GetScriptId() ? *Model->GetScriptId() : "";
    Value.Args = Model->GetArgs() ? *Model->GetArgs() : "";
    Value.MaxTryCount = Model->GetMaxTryCount() ? *Model->GetMaxTryCount() : 0;
    return Value;
}

inline Gs2::UE5::JobQueue::Model::FEzJobEntryPtr FGs2JobQueueJobEntryToEzJobEntry(
    const FGs2JobQueueJobEntry Model
)
{
    return MakeShared<Gs2::UE5::JobQueue::Model::FEzJobEntry>()
        ->WithScriptId(Model.ScriptId)
        ->WithArgs(Model.Args)
        ->WithMaxTryCount(Model.MaxTryCount);
}