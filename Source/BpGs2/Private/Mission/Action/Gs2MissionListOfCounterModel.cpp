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

#include "Mission/Action/Gs2MissionListOfCounterModel.h"
#include "Mission/Model/Gs2MissionCounterModel.h"
#include "Core/BpGs2Constant.h"

UGs2MissionListOfCounterModelAsyncFunction::UGs2MissionListOfCounterModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionListOfCounterModelAsyncFunction* UGs2MissionListOfCounterModelAsyncFunction::ListOfCounterModel(
    UObject* WorldContextObject,
    FGs2MissionNamespace Namespace
)
{
    UGs2MissionListOfCounterModelAsyncFunction* Action = NewObject<UGs2MissionListOfCounterModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionListOfCounterModelAsyncFunction::ListOfCounterModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2MissionListOfCounterModelAsyncFunction::Activate()
{
    TArray<FGs2MissionCounterModelValue> ReturnCounterModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionListOfCounterModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->CounterModels(
    );
    for (auto v : *It)
    {
        ReturnCounterModels.Add(EzCounterModelToFGs2MissionCounterModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnCounterModels, ReturnError);
}