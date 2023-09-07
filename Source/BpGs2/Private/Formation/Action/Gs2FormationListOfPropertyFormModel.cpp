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

#include "Formation/Action/Gs2FormationListOfPropertyFormModel.h"
#include "Formation/Model/Gs2FormationPropertyFormModel.h"
#include "Core/BpGs2Constant.h"

UGs2FormationListOfPropertyFormModelAsyncFunction::UGs2FormationListOfPropertyFormModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationListOfPropertyFormModelAsyncFunction* UGs2FormationListOfPropertyFormModelAsyncFunction::ListOfPropertyFormModel(
    UObject* WorldContextObject,
    FGs2FormationNamespace Namespace
)
{
    UGs2FormationListOfPropertyFormModelAsyncFunction* Action = NewObject<UGs2FormationListOfPropertyFormModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfPropertyFormModelAsyncFunction::ListOfPropertyFormModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2FormationListOfPropertyFormModelAsyncFunction::Activate()
{
    TArray<FGs2FormationPropertyFormModelValue> ReturnPropertyFormModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfPropertyFormModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->PropertyFormModels(
    );
    for (auto v : *It)
    {
        ReturnPropertyFormModels.Add(EzPropertyFormModelToFGs2FormationPropertyFormModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnPropertyFormModels, ReturnError);
}