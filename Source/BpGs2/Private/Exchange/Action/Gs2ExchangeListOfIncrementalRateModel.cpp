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

#include "Exchange/Action/Gs2ExchangeListOfIncrementalRateModel.h"
#include "Exchange/Model/Gs2ExchangeIncrementalRateModel.h"
#include "Core/BpGs2Constant.h"

UGs2ExchangeListOfIncrementalRateModelAsyncFunction::UGs2ExchangeListOfIncrementalRateModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExchangeListOfIncrementalRateModelAsyncFunction* UGs2ExchangeListOfIncrementalRateModelAsyncFunction::ListOfIncrementalRateModel(
    UObject* WorldContextObject,
    FGs2ExchangeNamespace Namespace
)
{
    UGs2ExchangeListOfIncrementalRateModelAsyncFunction* Action = NewObject<UGs2ExchangeListOfIncrementalRateModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeListOfIncrementalRateModelAsyncFunction::ListOfIncrementalRateModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2ExchangeListOfIncrementalRateModelAsyncFunction::Activate()
{
    TArray<FGs2ExchangeIncrementalRateModelValue> ReturnIncrementalRateModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeListOfIncrementalRateModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->IncrementalRateModels(
    );
    for (auto v : *It)
    {
        ReturnIncrementalRateModels.Add(EzIncrementalRateModelToFGs2ExchangeIncrementalRateModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnIncrementalRateModels, ReturnError);
}