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

#include "LoginReward/Action/Gs2LoginRewardReceiveStatusGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2LoginRewardReceiveStatusGetValueAsyncFunction::UGs2LoginRewardReceiveStatusGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LoginRewardReceiveStatusGetValueAsyncFunction* UGs2LoginRewardReceiveStatusGetValueAsyncFunction::ReceiveStatusGetValue(
    UObject* WorldContextObject,
    FGs2LoginRewardOwnReceiveStatus ReceiveStatus
)
{
    UGs2LoginRewardReceiveStatusGetValueAsyncFunction* Action = NewObject<UGs2LoginRewardReceiveStatusGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (ReceiveStatus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardReceiveStatusGetValueAsyncFunction::ReceiveStatusGetValue] ReceiveStatus parameter specification is missing."))
        return Action;
    }
    Action->ReceiveStatus = ReceiveStatus;
    return Action;
}

void UGs2LoginRewardReceiveStatusGetValueAsyncFunction::Activate()
{
    auto Future = ReceiveStatus.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzReceiveStatusToFGs2LoginRewardReceiveStatusValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2LoginRewardReceiveStatusValue ReturnReceiveStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnReceiveStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}