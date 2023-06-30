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

#include "Inventory/Action/Gs2InventoryListOfItemSet.h"
#include "Inventory/Model/Gs2InventoryItemSet.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfItemSetAsyncFunction::UGs2InventoryListOfItemSetAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfItemSetAsyncFunction* UGs2InventoryListOfItemSetAsyncFunction::ListOfItemSet(
    UObject* WorldContextObject,
    FGs2InventoryOwnInventory Inventory
)
{
    UGs2InventoryListOfItemSetAsyncFunction* Action = NewObject<UGs2InventoryListOfItemSetAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Inventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfItemSetAsyncFunction::ListOfItemSet] Inventory parameter specification is missing."))
        return Action;
    }
    Action->Inventory = Inventory;
    return Action;
}

void UGs2InventoryListOfItemSetAsyncFunction::Activate()
{
    TArray<FGs2InventoryItemSetValue> ReturnItemSets;
    FGs2Error ReturnError;

    if (Inventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfItemSetAsyncFunction::Activate] Inventory parameter specification is missing."))
        return;
    }
    const auto It = Inventory.Value->ItemSets(
    );
    for (auto v : *It)
    {
        ReturnItemSets.Add(EzItemSetToFGs2InventoryItemSetValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnItemSets, ReturnError);
}