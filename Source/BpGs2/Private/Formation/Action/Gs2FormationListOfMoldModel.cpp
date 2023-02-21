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

#include "Formation/Action/Gs2FormationListOfMoldModel.h"
#include "Formation/Model/Gs2FormationMoldModel.h"
#include "Core/BpGs2Constant.h"

UGs2FormationListOfMoldModelAsyncFunction::UGs2FormationListOfMoldModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationListOfMoldModelAsyncFunction* UGs2FormationListOfMoldModelAsyncFunction::ListOfMoldModel(
    UObject* WorldContextObject,
    FGs2FormationNamespace Namespace
)
{
    UGs2FormationListOfMoldModelAsyncFunction* Action = NewObject<UGs2FormationListOfMoldModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfMoldModelAsyncFunction::ListOfMoldModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2FormationListOfMoldModelAsyncFunction::Activate()
{
    TArray<FGs2FormationMoldModelValue> ReturnMoldModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->MoldModels(
    );
    for (auto v : *It)
    {
        ReturnMoldModels.Add(EzMoldModelToFGs2FormationMoldModelValue(v));
    }
    OnSuccess.Broadcast(ReturnMoldModels, ReturnError);
}