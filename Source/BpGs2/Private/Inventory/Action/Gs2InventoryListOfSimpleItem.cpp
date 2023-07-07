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

#include "Inventory/Action/Gs2InventoryListOfSimpleItem.h"
#include "Inventory/Model/Gs2InventorySimpleItem.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfSimpleItemAsyncFunction::UGs2InventoryListOfSimpleItemAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfSimpleItemAsyncFunction* UGs2InventoryListOfSimpleItemAsyncFunction::ListOfSimpleItem(
    UObject* WorldContextObject,
    FGs2InventoryOwnSimpleInventory SimpleInventory
)
{
    UGs2InventoryListOfSimpleItemAsyncFunction* Action = NewObject<UGs2InventoryListOfSimpleItemAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SimpleInventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfSimpleItemAsyncFunction::ListOfSimpleItem] SimpleInventory parameter specification is missing."))
        return Action;
    }
    Action->SimpleInventory = SimpleInventory;
    return Action;
}

void UGs2InventoryListOfSimpleItemAsyncFunction::Activate()
{
    TArray<FGs2InventorySimpleItemValue> ReturnSimpleItems;
    FGs2Error ReturnError;

    if (SimpleInventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfSimpleItemAsyncFunction::Activate] SimpleInventory parameter specification is missing."))
        return;
    }
    const auto It = SimpleInventory.Value->SimpleItems(
    );
    for (auto v : *It)
    {
        ReturnSimpleItems.Add(EzSimpleItemToFGs2InventorySimpleItemValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnSimpleItems, ReturnError);
}