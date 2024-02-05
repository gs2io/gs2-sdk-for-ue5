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

#include "Schedule/Action/Gs2ScheduleEventGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ScheduleEventGetValueAsyncFunction::UGs2ScheduleEventGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ScheduleEventGetValueAsyncFunction* UGs2ScheduleEventGetValueAsyncFunction::EventGetValue(
    UObject* WorldContextObject,
    FGs2ScheduleOwnEvent Event
)
{
    UGs2ScheduleEventGetValueAsyncFunction* Action = NewObject<UGs2ScheduleEventGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Event.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleEventGetValueAsyncFunction::EventGetValue] Event parameter specification is missing."))
        return Action;
    }
    Action->Event = Event;
    return Action;
}

void UGs2ScheduleEventGetValueAsyncFunction::Activate()
{
    auto Future = Event.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzEventToFGs2ScheduleEventValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ScheduleEventValue ReturnEvent;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnEvent, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}