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

#include "Schedule/Action/Gs2ScheduleListOfTrigger.h"
#include "Schedule/Model/Gs2ScheduleTrigger.h"
#include "Core/BpGs2Constant.h"

UGs2ScheduleListOfTriggerAsyncFunction::UGs2ScheduleListOfTriggerAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ScheduleListOfTriggerAsyncFunction* UGs2ScheduleListOfTriggerAsyncFunction::ListOfTrigger(
    UObject* WorldContextObject,
    FGs2ScheduleOwnUser User
)
{
    UGs2ScheduleListOfTriggerAsyncFunction* Action = NewObject<UGs2ScheduleListOfTriggerAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ScheduleListOfTriggerAsyncFunction::ListOfTrigger] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2ScheduleListOfTriggerAsyncFunction::Activate()
{
    TArray<FGs2ScheduleTriggerValue> ReturnTriggers;
    FGs2Error ReturnError;
    const auto It = User.Value->Triggers(
    );
    for (auto v : *It)
    {
        ReturnTriggers.Add(EzTriggerToFGs2ScheduleTriggerValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnTriggers, ReturnError);
}