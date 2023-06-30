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

#include "Idle/Action/Gs2IdleListOfStatus.h"
#include "Idle/Model/Gs2IdleStatus.h"
#include "Core/BpGs2Constant.h"

UGs2IdleListOfStatusAsyncFunction::UGs2IdleListOfStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2IdleListOfStatusAsyncFunction* UGs2IdleListOfStatusAsyncFunction::ListOfStatus(
    UObject* WorldContextObject,
    FGs2IdleOwnUser User
)
{
    UGs2IdleListOfStatusAsyncFunction* Action = NewObject<UGs2IdleListOfStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleListOfStatusAsyncFunction::ListOfStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2IdleListOfStatusAsyncFunction::Activate()
{
    TArray<FGs2IdleStatusValue> ReturnStatuses;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleListOfStatusAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Statuses(
    );
    for (auto v : *It)
    {
        ReturnStatuses.Add(EzStatusToFGs2IdleStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnStatuses, ReturnError);
}