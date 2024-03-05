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

#include "JobQueue/Action/Gs2JobQueueJobResultGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2JobQueueJobResultGetValueAsyncFunction::UGs2JobQueueJobResultGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2JobQueueJobResultGetValueAsyncFunction* UGs2JobQueueJobResultGetValueAsyncFunction::JobResultGetValue(
    UObject* WorldContextObject,
    FGs2JobQueueOwnJobResult JobResult
)
{
    UGs2JobQueueJobResultGetValueAsyncFunction* Action = NewObject<UGs2JobQueueJobResultGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (JobResult.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2JobQueueJobResultGetValueAsyncFunction::JobResultGetValue] JobResult parameter specification is missing."))
        return Action;
    }
    Action->JobResult = JobResult;
    return Action;
}

void UGs2JobQueueJobResultGetValueAsyncFunction::Activate()
{
    auto Future = JobResult.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzJobResultToFGs2JobQueueJobResultValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2JobQueueJobResultValue ReturnJobResult;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnJobResult, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}