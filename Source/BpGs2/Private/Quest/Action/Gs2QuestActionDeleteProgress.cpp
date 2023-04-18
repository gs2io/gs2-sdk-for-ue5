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

#include "Quest/Action/Gs2QuestActionDeleteProgress.h"
#include "Core/BpGs2Constant.h"

UGs2QuestDeleteProgressAsyncFunction::UGs2QuestDeleteProgressAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestDeleteProgressAsyncFunction* UGs2QuestDeleteProgressAsyncFunction::DeleteProgress(
    UObject* WorldContextObject,
    FGs2QuestOwnProgress Progress
)
{
    UGs2QuestDeleteProgressAsyncFunction* Action = NewObject<UGs2QuestDeleteProgressAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestDeleteProgressAsyncFunction::DeleteProgress] Progress parameter specification is missing."))
        return Action;
    }
    Action->Progress = Progress;
    return Action;
}

void UGs2QuestDeleteProgressAsyncFunction::Activate()
{
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestDeleteProgressAsyncFunction] Progress parameter specification is missing."))
        return;
    }

    auto Future = Progress.Value->DeleteProgress(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2QuestOwnProgress ReturnProgress;
        ReturnProgress.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnProgress, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2QuestOwnProgress ReturnProgress;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnProgress, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}