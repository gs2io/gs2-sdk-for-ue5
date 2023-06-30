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

#include "Inventory/Action/Gs2InventoryListOfItemModel.h"
#include "Inventory/Model/Gs2InventoryItemModel.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfItemModelAsyncFunction::UGs2InventoryListOfItemModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfItemModelAsyncFunction* UGs2InventoryListOfItemModelAsyncFunction::ListOfItemModel(
    UObject* WorldContextObject,
    FGs2InventoryInventoryModel InventoryModel
)
{
    UGs2InventoryListOfItemModelAsyncFunction* Action = NewObject<UGs2InventoryListOfItemModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (InventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfItemModelAsyncFunction::ListOfItemModel] InventoryModel parameter specification is missing."))
        return Action;
    }
    Action->InventoryModel = InventoryModel;
    return Action;
}

void UGs2InventoryListOfItemModelAsyncFunction::Activate()
{
    TArray<FGs2InventoryItemModelValue> ReturnItemModels;
    FGs2Error ReturnError;

    if (InventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfItemModelAsyncFunction::Activate] InventoryModel parameter specification is missing."))
        return;
    }
    const auto It = InventoryModel.Value->ItemModels(
    );
    for (auto v : *It)
    {
        ReturnItemModels.Add(EzItemModelToFGs2InventoryItemModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnItemModels, ReturnError);
}