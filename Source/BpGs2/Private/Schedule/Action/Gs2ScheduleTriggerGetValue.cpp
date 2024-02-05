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

#include "Schedule/Action/Gs2ScheduleTriggerGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ScheduleTriggerGetValueAsyncFunction::UGs2ScheduleTriggerGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ScheduleTriggerGetValueAsyncFunction* UGs2ScheduleTriggerGetValueAsyncFunction::TriggerGetValue(
    UObject* WorldContextObject,
    FGs2ScheduleOwnTrigger Trigger
)
{
    UGs2ScheduleTriggerGetValueAsyncFunction* Action = NewObject<UGs2ScheduleTriggerGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Trigger.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleTriggerGetValueAsyncFunction::TriggerGetValue] Trigger parameter specification is missing."))
        return Action;
    }
    Action->Trigger = Trigger;
    return Action;
}

void UGs2ScheduleTriggerGetValueAsyncFunction::Activate()
{
    auto Future = Trigger.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzTriggerToFGs2ScheduleTriggerValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ScheduleTriggerValue ReturnTrigger;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTrigger, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}