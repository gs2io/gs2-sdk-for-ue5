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

#include "Mission/Action/Gs2MissionListOfComplete.h"
#include "Mission/Model/Gs2MissionComplete.h"
#include "Core/BpGs2Constant.h"

UGs2MissionListOfCompleteAsyncFunction::UGs2MissionListOfCompleteAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MissionListOfCompleteAsyncFunction* UGs2MissionListOfCompleteAsyncFunction::ListOfComplete(
    UObject* WorldContextObject,
    FGs2MissionOwnUser User
)
{
    UGs2MissionListOfCompleteAsyncFunction* Action = NewObject<UGs2MissionListOfCompleteAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MissionListOfCompleteAsyncFunction::ListOfComplete] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2MissionListOfCompleteAsyncFunction::Activate()
{
    TArray<FGs2MissionCompleteValue> ReturnCompletes;
    FGs2Error ReturnError;
    const auto It = User.Value->Completes(
    );
    for (auto v : *It)
    {
        ReturnCompletes.Add(EzCompleteToFGs2MissionCompleteValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnCompletes, ReturnError);
}