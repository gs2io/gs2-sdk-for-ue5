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

#include "Inventory/Action/Gs2InventoryListOfInventoryModel.h"
#include "Inventory/Model/Gs2InventoryInventoryModel.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfInventoryModelAsyncFunction::UGs2InventoryListOfInventoryModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfInventoryModelAsyncFunction* UGs2InventoryListOfInventoryModelAsyncFunction::ListOfInventoryModel(
    UObject* WorldContextObject,
    FGs2InventoryNamespace Namespace
)
{
    UGs2InventoryListOfInventoryModelAsyncFunction* Action = NewObject<UGs2InventoryListOfInventoryModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfInventoryModelAsyncFunction::ListOfInventoryModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2InventoryListOfInventoryModelAsyncFunction::Activate()
{
    TArray<FGs2InventoryInventoryModelValue> ReturnInventoryModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->InventoryModels(
    );
    for (auto v : *It)
    {
        ReturnInventoryModels.Add(EzInventoryModelToFGs2InventoryInventoryModelValue(v));
    }
    OnSuccess.Broadcast(ReturnInventoryModels, ReturnError);
}