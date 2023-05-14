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

#include "Mission/Action/Gs2MissionListOfMissionGroupModel.h"
#include "Mission/Model/Gs2MissionMissionGroupModel.h"
#include "Core/BpGs2Constant.h"

UGs2MissionListOfMissionGroupModelAsyncFunction::UGs2MissionListOfMissionGroupModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionListOfMissionGroupModelAsyncFunction* UGs2MissionListOfMissionGroupModelAsyncFunction::ListOfMissionGroupModel(
    UObject* WorldContextObject,
    FGs2MissionNamespace Namespace
)
{
    UGs2MissionListOfMissionGroupModelAsyncFunction* Action = NewObject<UGs2MissionListOfMissionGroupModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionListOfMissionGroupModelAsyncFunction::ListOfMissionGroupModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2MissionListOfMissionGroupModelAsyncFunction::Activate()
{
    TArray<FGs2MissionMissionGroupModelValue> ReturnMissionGroupModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->MissionGroupModels(
    );
    for (auto v : *It)
    {
        ReturnMissionGroupModels.Add(EzMissionGroupModelToFGs2MissionMissionGroupModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnMissionGroupModels, ReturnError);
}