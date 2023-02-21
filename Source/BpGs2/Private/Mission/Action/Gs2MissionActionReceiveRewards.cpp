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

#include "Mission/Action/Gs2MissionActionReceiveRewards.h"
#include "Core/BpGs2Constant.h"

UGs2MissionReceiveRewardsAsyncFunction::UGs2MissionReceiveRewardsAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionReceiveRewardsAsyncFunction* UGs2MissionReceiveRewardsAsyncFunction::ReceiveRewards(
    UObject* WorldContextObject,
    FGs2MissionOwnComplete Complete,
    FString MissionTaskName
)
{
    UGs2MissionReceiveRewardsAsyncFunction* Action = NewObject<UGs2MissionReceiveRewardsAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Complete.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionReceiveRewardsAsyncFunction::ReceiveRewards] Complete parameter specification is missing."))
        return Action;
    }
    Action->Complete = Complete;
    Action->MissionTaskName = MissionTaskName;
    return Action;
}

void UGs2MissionReceiveRewardsAsyncFunction::Activate()
{
    if (Complete.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionReceiveRewardsAsyncFunction] Complete parameter specification is missing."))
        return;
    }

    auto Future = Complete.Value->ReceiveRewards(
        MissionTaskName
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2MissionOwnComplete ReturnComplete;
        ReturnComplete.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnComplete, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2MissionOwnComplete ReturnComplete;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnComplete, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}