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

#include "Mission/Action/Gs2MissionCompleteGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MissionCompleteGetValueAsyncFunction::UGs2MissionCompleteGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionCompleteGetValueAsyncFunction* UGs2MissionCompleteGetValueAsyncFunction::CompleteGetValue(
    UObject* WorldContextObject,
    FGs2MissionOwnComplete Complete
)
{
    UGs2MissionCompleteGetValueAsyncFunction* Action = NewObject<UGs2MissionCompleteGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Complete.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionCompleteGetValueAsyncFunction::CompleteGetValue] Complete parameter specification is missing."))
        return Action;
    }
    Action->Complete = Complete;
    return Action;
}

void UGs2MissionCompleteGetValueAsyncFunction::Activate()
{
    auto Future = Complete.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzCompleteToFGs2MissionCompleteValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MissionCompleteValue ReturnComplete;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnComplete, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}