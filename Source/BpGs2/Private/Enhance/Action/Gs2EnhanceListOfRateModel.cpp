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

#include "Enhance/Action/Gs2EnhanceListOfRateModel.h"
#include "Enhance/Model/Gs2EnhanceRateModel.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceListOfRateModelAsyncFunction::UGs2EnhanceListOfRateModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceListOfRateModelAsyncFunction* UGs2EnhanceListOfRateModelAsyncFunction::ListOfRateModel(
    UObject* WorldContextObject,
    FGs2EnhanceNamespace Namespace
)
{
    UGs2EnhanceListOfRateModelAsyncFunction* Action = NewObject<UGs2EnhanceListOfRateModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceListOfRateModelAsyncFunction::ListOfRateModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2EnhanceListOfRateModelAsyncFunction::Activate()
{
    TArray<FGs2EnhanceRateModelValue> ReturnRateModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->RateModels(
    );
    for (auto v : *It)
    {
        ReturnRateModels.Add(EzRateModelToFGs2EnhanceRateModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnRateModels, ReturnError);
}