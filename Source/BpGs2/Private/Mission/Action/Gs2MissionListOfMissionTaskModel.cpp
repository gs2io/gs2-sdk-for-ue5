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

#include "Mission/Action/Gs2MissionListOfMissionTaskModel.h"
#include "Mission/Model/Gs2MissionMissionTaskModel.h"
#include "Core/BpGs2Constant.h"

UGs2MissionListOfMissionTaskModelAsyncFunction::UGs2MissionListOfMissionTaskModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionListOfMissionTaskModelAsyncFunction* UGs2MissionListOfMissionTaskModelAsyncFunction::ListOfMissionTaskModel(
    UObject* WorldContextObject,
    FGs2MissionMissionGroupModel MissionGroupModel
)
{
    UGs2MissionListOfMissionTaskModelAsyncFunction* Action = NewObject<UGs2MissionListOfMissionTaskModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (MissionGroupModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionListOfMissionTaskModelAsyncFunction::ListOfMissionTaskModel] MissionGroupModel parameter specification is missing."))
        return Action;
    }
    Action->MissionGroupModel = MissionGroupModel;
    return Action;
}

void UGs2MissionListOfMissionTaskModelAsyncFunction::Activate()
{
    TArray<FGs2MissionMissionTaskModelValue> ReturnMissionTaskModels;
    FGs2Error ReturnError;
    const auto It = MissionGroupModel.Value->MissionTaskModels(
    );
    for (auto v : *It)
    {
        ReturnMissionTaskModels.Add(EzMissionTaskModelToFGs2MissionMissionTaskModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnMissionTaskModels, ReturnError);
}