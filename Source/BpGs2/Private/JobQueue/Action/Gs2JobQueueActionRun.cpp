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

#include "JobQueue/Action/Gs2JobQueueActionRun.h"
#include "Core/BpGs2Constant.h"

UGs2JobQueueRunAsyncFunction::UGs2JobQueueRunAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2JobQueueRunAsyncFunction* UGs2JobQueueRunAsyncFunction::Run(
    UObject* WorldContextObject,
    FGs2JobQueueOwnUser User
)
{
    UGs2JobQueueRunAsyncFunction* Action = NewObject<UGs2JobQueueRunAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2JobQueueRunAsyncFunction::Run] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2JobQueueRunAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2JobQueueRunAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->Run(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2JobQueueOwnJob ReturnJob;
        ReturnJob.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnJob, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2JobQueueOwnJob ReturnJob;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnJob, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}