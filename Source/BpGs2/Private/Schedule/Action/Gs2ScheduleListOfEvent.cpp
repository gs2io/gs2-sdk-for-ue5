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

#include "Schedule/Action/Gs2ScheduleListOfEvent.h"
#include "Schedule/Model/Gs2ScheduleEvent.h"
#include "Core/BpGs2Constant.h"

UGs2ScheduleListOfEventAsyncFunction::UGs2ScheduleListOfEventAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ScheduleListOfEventAsyncFunction* UGs2ScheduleListOfEventAsyncFunction::ListOfEvent(
    UObject* WorldContextObject,
    FGs2ScheduleOwnUser User
)
{
    UGs2ScheduleListOfEventAsyncFunction* Action = NewObject<UGs2ScheduleListOfEventAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleListOfEventAsyncFunction::ListOfEvent] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2ScheduleListOfEventAsyncFunction::Activate()
{
    TArray<FGs2ScheduleEventValue> ReturnEvents;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleListOfEventAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Events(
    );
    for (auto v : *It)
    {
        ReturnEvents.Add(EzEventToFGs2ScheduleEventValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnEvents, ReturnError);
}