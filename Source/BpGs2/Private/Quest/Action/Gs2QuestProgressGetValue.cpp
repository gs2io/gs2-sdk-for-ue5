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

#include "Quest/Action/Gs2QuestProgressGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2QuestProgressGetValueAsyncFunction::UGs2QuestProgressGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestProgressGetValueAsyncFunction* UGs2QuestProgressGetValueAsyncFunction::ProgressGetValue(
    UObject* WorldContextObject,
    FGs2QuestOwnProgress Progress
)
{
    UGs2QuestProgressGetValueAsyncFunction* Action = NewObject<UGs2QuestProgressGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestProgressGetValueAsyncFunction::ProgressGetValue] Progress parameter specification is missing."))
        return Action;
    }
    Action->Progress = Progress;
    return Action;
}

void UGs2QuestProgressGetValueAsyncFunction::Activate()
{
    auto Future = Progress.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzProgressToFGs2QuestProgressValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2QuestProgressValue ReturnProgress;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnProgress, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}