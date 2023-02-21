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

#include "Mission/Action/Gs2MissionMissionTaskModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MissionMissionTaskModelGetValueAsyncFunction::UGs2MissionMissionTaskModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionMissionTaskModelGetValueAsyncFunction* UGs2MissionMissionTaskModelGetValueAsyncFunction::MissionTaskModelGetValue(
    UObject* WorldContextObject,
    FGs2MissionMissionTaskModel MissionTaskModel
)
{
    UGs2MissionMissionTaskModelGetValueAsyncFunction* Action = NewObject<UGs2MissionMissionTaskModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (MissionTaskModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionMissionTaskModelGetValueAsyncFunction::MissionTaskModelGetValue] MissionTaskModel parameter specification is missing."))
        return Action;
    }
    Action->MissionTaskModel = MissionTaskModel;
    return Action;
}

void UGs2MissionMissionTaskModelGetValueAsyncFunction::Activate()
{
    auto Future = MissionTaskModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzMissionTaskModelToFGs2MissionMissionTaskModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MissionMissionTaskModelValue ReturnMissionTaskModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnMissionTaskModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}