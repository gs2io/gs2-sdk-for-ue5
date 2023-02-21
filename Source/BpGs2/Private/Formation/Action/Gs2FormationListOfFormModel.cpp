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

#include "Formation/Action/Gs2FormationListOfFormModel.h"
#include "Formation/Model/Gs2FormationFormModel.h"
#include "Core/BpGs2Constant.h"

UGs2FormationListOfFormModelAsyncFunction::UGs2FormationListOfFormModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2FormationListOfFormModelAsyncFunction* UGs2FormationListOfFormModelAsyncFunction::ListOfFormModel(
    UObject* WorldContextObject,
    FGs2FormationNamespace Namespace
)
{
    UGs2FormationListOfFormModelAsyncFunction* Action = NewObject<UGs2FormationListOfFormModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2FormationListOfFormModelAsyncFunction::ListOfFormModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2FormationListOfFormModelAsyncFunction::Activate()
{
    TArray<FGs2FormationFormModelValue> ReturnFormModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->FormModels(
    );
    for (auto v : *It)
    {
        ReturnFormModels.Add(EzFormModelToFGs2FormationFormModelValue(v));
    }
    OnSuccess.Broadcast(ReturnFormModels, ReturnError);
}