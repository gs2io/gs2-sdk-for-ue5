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

#include "Mission/Action/Gs2MissionMissionGroupModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MissionMissionGroupModelGetValueAsyncFunction::UGs2MissionMissionGroupModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionMissionGroupModelGetValueAsyncFunction* UGs2MissionMissionGroupModelGetValueAsyncFunction::MissionGroupModelGetValue(
    UObject* WorldContextObject,
    FGs2MissionMissionGroupModel MissionGroupModel
)
{
    UGs2MissionMissionGroupModelGetValueAsyncFunction* Action = NewObject<UGs2MissionMissionGroupModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (MissionGroupModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionMissionGroupModelGetValueAsyncFunction::MissionGroupModelGetValue] MissionGroupModel parameter specification is missing."))
        return Action;
    }
    Action->MissionGroupModel = MissionGroupModel;
    return Action;
}

void UGs2MissionMissionGroupModelGetValueAsyncFunction::Activate()
{
    auto Future = MissionGroupModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzMissionGroupModelToFGs2MissionMissionGroupModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MissionMissionGroupModelValue ReturnMissionGroupModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnMissionGroupModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}