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

#include "Stamina/Action/Gs2StaminaListOfStaminaModel.h"
#include "Stamina/Model/Gs2StaminaStaminaModel.h"
#include "Core/BpGs2Constant.h"

UGs2StaminaListOfStaminaModelAsyncFunction::UGs2StaminaListOfStaminaModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2StaminaListOfStaminaModelAsyncFunction* UGs2StaminaListOfStaminaModelAsyncFunction::ListOfStaminaModel(
    UObject* WorldContextObject,
    FGs2StaminaNamespace Namespace
)
{
    UGs2StaminaListOfStaminaModelAsyncFunction* Action = NewObject<UGs2StaminaListOfStaminaModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaListOfStaminaModelAsyncFunction::ListOfStaminaModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2StaminaListOfStaminaModelAsyncFunction::Activate()
{
    TArray<FGs2StaminaStaminaModelValue> ReturnStaminaModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->StaminaModels(
    );
    for (auto v : *It)
    {
        ReturnStaminaModels.Add(EzStaminaModelToFGs2StaminaStaminaModelValue(v));
    }
    OnSuccess.Broadcast(ReturnStaminaModels, ReturnError);
}