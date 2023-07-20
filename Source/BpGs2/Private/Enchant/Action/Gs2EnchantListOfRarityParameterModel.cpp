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

#include "Enchant/Action/Gs2EnchantListOfRarityParameterModel.h"
#include "Enchant/Model/Gs2EnchantRarityParameterModel.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantListOfRarityParameterModelAsyncFunction::UGs2EnchantListOfRarityParameterModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantListOfRarityParameterModelAsyncFunction* UGs2EnchantListOfRarityParameterModelAsyncFunction::ListOfRarityParameterModel(
    UObject* WorldContextObject,
    FGs2EnchantNamespace Namespace
)
{
    UGs2EnchantListOfRarityParameterModelAsyncFunction* Action = NewObject<UGs2EnchantListOfRarityParameterModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantListOfRarityParameterModelAsyncFunction::ListOfRarityParameterModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2EnchantListOfRarityParameterModelAsyncFunction::Activate()
{
    TArray<FGs2EnchantRarityParameterModelValue> ReturnRarityParameterModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantListOfRarityParameterModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->RarityParameterModels(
    );
    for (auto v : *It)
    {
        ReturnRarityParameterModels.Add(EzRarityParameterModelToFGs2EnchantRarityParameterModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnRarityParameterModels, ReturnError);
}