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

#include "LoginReward/Action/Gs2LoginRewardListOfReceiveStatus.h"
#include "LoginReward/Model/Gs2LoginRewardReceiveStatus.h"
#include "Core/BpGs2Constant.h"

UGs2LoginRewardListOfReceiveStatusAsyncFunction::UGs2LoginRewardListOfReceiveStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LoginRewardListOfReceiveStatusAsyncFunction* UGs2LoginRewardListOfReceiveStatusAsyncFunction::ListOfReceiveStatus(
    UObject* WorldContextObject,
    FGs2LoginRewardOwnUser User
)
{
    UGs2LoginRewardListOfReceiveStatusAsyncFunction* Action = NewObject<UGs2LoginRewardListOfReceiveStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardListOfReceiveStatusAsyncFunction::ListOfReceiveStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2LoginRewardListOfReceiveStatusAsyncFunction::Activate()
{
    TArray<FGs2LoginRewardReceiveStatusValue> ReturnReceiveStatuses;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardListOfReceiveStatusAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->ReceiveStatuses(
    );
    for (auto v : *It)
    {
        ReturnReceiveStatuses.Add(EzReceiveStatusToFGs2LoginRewardReceiveStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnReceiveStatuses, ReturnError);
}