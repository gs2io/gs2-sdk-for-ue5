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

#include "StateMachine/Action/Gs2StateMachineListOfStatus.h"
#include "StateMachine/Model/Gs2StateMachineStatus.h"
#include "Core/BpGs2Constant.h"

UGs2StateMachineListOfStatusAsyncFunction::UGs2StateMachineListOfStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2StateMachineListOfStatusAsyncFunction* UGs2StateMachineListOfStatusAsyncFunction::ListOfStatus(
    UObject* WorldContextObject,
    FGs2StateMachineOwnUser User,
    FString Status
)
{
    UGs2StateMachineListOfStatusAsyncFunction* Action = NewObject<UGs2StateMachineListOfStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StateMachineListOfStatusAsyncFunction::ListOfStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->Status = Status;
    return Action;
}

void UGs2StateMachineListOfStatusAsyncFunction::Activate()
{
    TArray<FGs2StateMachineStatusValue> ReturnStatuses;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StateMachineListOfStatusAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Statuses(
        Status
    );
    for (auto v : *It)
    {
        ReturnStatuses.Add(EzStatusToFGs2StateMachineStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnStatuses, ReturnError);
}