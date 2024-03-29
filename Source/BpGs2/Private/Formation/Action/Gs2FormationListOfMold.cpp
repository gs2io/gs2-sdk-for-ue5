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

#include "Formation/Action/Gs2FormationListOfMold.h"
#include "Formation/Model/Gs2FormationMold.h"
#include "Core/BpGs2Constant.h"

UGs2FormationListOfMoldAsyncFunction::UGs2FormationListOfMoldAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationListOfMoldAsyncFunction* UGs2FormationListOfMoldAsyncFunction::ListOfMold(
    UObject* WorldContextObject,
    FGs2FormationOwnUser User
)
{
    UGs2FormationListOfMoldAsyncFunction* Action = NewObject<UGs2FormationListOfMoldAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfMoldAsyncFunction::ListOfMold] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2FormationListOfMoldAsyncFunction::Activate()
{
    TArray<FGs2FormationMoldValue> ReturnMolds;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfMoldAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Molds(
    );
    for (auto v : *It)
    {
        ReturnMolds.Add(EzMoldToFGs2FormationMoldValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnMolds, ReturnError);
}