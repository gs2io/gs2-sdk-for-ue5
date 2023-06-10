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
 *
 * deny overwrite
 */

#include "Idle/Action/Gs2IdleActionPrediction.h"
#include "Core/BpGs2Constant.h"

UGs2IdlePredictionAsyncFunction::UGs2IdlePredictionAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2IdlePredictionAsyncFunction* UGs2IdlePredictionAsyncFunction::Prediction(
    UObject* WorldContextObject,
    FGs2IdleOwnStatus Status
)
{
    UGs2IdlePredictionAsyncFunction* Action = NewObject<UGs2IdlePredictionAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdlePredictionAsyncFunction::Prediction] Status parameter specification is missing."))
        return Action;
    }
    Action->Status = Status;
    return Action;
}

void UGs2IdlePredictionAsyncFunction::Activate()
{
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdlePredictionAsyncFunction] Status parameter specification is missing."))
        return;
    }

    auto Future = Status.Value->Prediction(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        auto ReturnAcquireAction = [&]
        {
            TArray<FGs2IdleAcquireAction> r;
            for (auto v : *Result)
            {
                r.Add(EzAcquireActionToFGs2IdleAcquireAction(v));
            }
            return r;
        }();
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnAcquireAction, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        TArray<FGs2IdleAcquireAction> ReturnAcquireAction;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnSuccess.Broadcast(ReturnAcquireAction, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}