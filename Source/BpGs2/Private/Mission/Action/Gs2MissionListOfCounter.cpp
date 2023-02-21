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

#include "Mission/Action/Gs2MissionListOfCounter.h"
#include "Mission/Model/Gs2MissionCounter.h"
#include "Core/BpGs2Constant.h"

UGs2MissionListOfCounterAsyncFunction::UGs2MissionListOfCounterAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionListOfCounterAsyncFunction* UGs2MissionListOfCounterAsyncFunction::ListOfCounter(
    UObject* WorldContextObject,
    FGs2MissionOwnUser User
)
{
    UGs2MissionListOfCounterAsyncFunction* Action = NewObject<UGs2MissionListOfCounterAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionListOfCounterAsyncFunction::ListOfCounter] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2MissionListOfCounterAsyncFunction::Activate()
{
    TArray<FGs2MissionCounterValue> ReturnCounters;
    FGs2Error ReturnError;
    const auto It = User.Value->Counters(
    );
    for (auto v : *It)
    {
        ReturnCounters.Add(EzCounterToFGs2MissionCounterValue(v));
    }
    OnSuccess.Broadcast(ReturnCounters, ReturnError);
}