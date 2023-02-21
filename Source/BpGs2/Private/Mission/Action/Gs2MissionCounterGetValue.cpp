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

#include "Mission/Action/Gs2MissionCounterGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MissionCounterGetValueAsyncFunction::UGs2MissionCounterGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionCounterGetValueAsyncFunction* UGs2MissionCounterGetValueAsyncFunction::CounterGetValue(
    UObject* WorldContextObject,
    FGs2MissionOwnCounter Counter
)
{
    UGs2MissionCounterGetValueAsyncFunction* Action = NewObject<UGs2MissionCounterGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Counter.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionCounterGetValueAsyncFunction::CounterGetValue] Counter parameter specification is missing."))
        return Action;
    }
    Action->Counter = Counter;
    return Action;
}

void UGs2MissionCounterGetValueAsyncFunction::Activate()
{
    auto Future = Counter.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzCounterToFGs2MissionCounterValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MissionCounterValue ReturnCounter;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnCounter, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}