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

#include "Enhance/Action/Gs2EnhanceActionDeleteProgress.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceDeleteProgressAsyncFunction::UGs2EnhanceDeleteProgressAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceDeleteProgressAsyncFunction* UGs2EnhanceDeleteProgressAsyncFunction::DeleteProgress(
    UObject* WorldContextObject,
    FGs2EnhanceOwnProgress Progress
)
{
    UGs2EnhanceDeleteProgressAsyncFunction* Action = NewObject<UGs2EnhanceDeleteProgressAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceDeleteProgressAsyncFunction::DeleteProgress] Progress parameter specification is missing."))
        return Action;
    }
    Action->Progress = Progress;
    return Action;
}

void UGs2EnhanceDeleteProgressAsyncFunction::Activate()
{
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceDeleteProgressAsyncFunction] Progress parameter specification is missing."))
        return;
    }

    auto Future = Progress.Value->DeleteProgress(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2EnhanceOwnProgress ReturnProgress;
        ReturnProgress.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnProgress, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2EnhanceOwnProgress ReturnProgress;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnProgress, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}