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

#include "Limit/Action/Gs2LimitListOfCounter.h"
#include "Limit/Model/Gs2LimitCounter.h"
#include "Core/BpGs2Constant.h"

UGs2LimitListOfCounterAsyncFunction::UGs2LimitListOfCounterAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LimitListOfCounterAsyncFunction* UGs2LimitListOfCounterAsyncFunction::ListOfCounter(
    UObject* WorldContextObject,
    FGs2LimitOwnUser User,
    FString LimitName
)
{
    UGs2LimitListOfCounterAsyncFunction* Action = NewObject<UGs2LimitListOfCounterAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitListOfCounterAsyncFunction::ListOfCounter] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->LimitName = LimitName;
    return Action;
}

void UGs2LimitListOfCounterAsyncFunction::Activate()
{
    TArray<FGs2LimitCounterValue> ReturnCounters;
    FGs2Error ReturnError;
    const auto It = User.Value->Counters(
        LimitName
    );
    for (auto v : *It)
    {
        ReturnCounters.Add(EzCounterToFGs2LimitCounterValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnCounters, ReturnError);
}