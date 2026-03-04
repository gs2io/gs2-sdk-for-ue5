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

#include "Enhance/Action/Gs2EnhanceListOfUnleashRateModel.h"
#include "Enhance/Model/Gs2EnhanceUnleashRateModel.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceListOfUnleashRateModelAsyncFunction::UGs2EnhanceListOfUnleashRateModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceListOfUnleashRateModelAsyncFunction* UGs2EnhanceListOfUnleashRateModelAsyncFunction::ListOfUnleashRateModel(
    UObject* WorldContextObject,
    FGs2EnhanceNamespace Namespace
)
{
    UGs2EnhanceListOfUnleashRateModelAsyncFunction* Action = NewObject<UGs2EnhanceListOfUnleashRateModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceListOfUnleashRateModelAsyncFunction::ListOfUnleashRateModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2EnhanceListOfUnleashRateModelAsyncFunction::Activate()
{
    TArray<FGs2EnhanceUnleashRateModelValue> ReturnUnleashRateModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceListOfUnleashRateModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->UnleashRateModels(
    );
    for (auto v : *It)
    {
        ReturnUnleashRateModels.Add(EzUnleashRateModelToFGs2EnhanceUnleashRateModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnUnleashRateModels, ReturnError);
}