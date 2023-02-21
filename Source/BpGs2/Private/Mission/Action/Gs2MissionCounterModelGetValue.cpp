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

#include "Mission/Action/Gs2MissionCounterModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MissionCounterModelGetValueAsyncFunction::UGs2MissionCounterModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionCounterModelGetValueAsyncFunction* UGs2MissionCounterModelGetValueAsyncFunction::CounterModelGetValue(
    UObject* WorldContextObject,
    FGs2MissionCounterModel CounterModel
)
{
    UGs2MissionCounterModelGetValueAsyncFunction* Action = NewObject<UGs2MissionCounterModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (CounterModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionCounterModelGetValueAsyncFunction::CounterModelGetValue] CounterModel parameter specification is missing."))
        return Action;
    }
    Action->CounterModel = CounterModel;
    return Action;
}

void UGs2MissionCounterModelGetValueAsyncFunction::Activate()
{
    auto Future = CounterModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzCounterModelToFGs2MissionCounterModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MissionCounterModelValue ReturnCounterModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnCounterModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}