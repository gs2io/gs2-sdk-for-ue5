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

#include "Inventory/Action/Gs2InventoryListOfBigItem.h"
#include "Inventory/Model/Gs2InventoryBigItem.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfBigItemAsyncFunction::UGs2InventoryListOfBigItemAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfBigItemAsyncFunction* UGs2InventoryListOfBigItemAsyncFunction::ListOfBigItem(
    UObject* WorldContextObject,
    FGs2InventoryOwnBigInventory BigInventory
)
{
    UGs2InventoryListOfBigItemAsyncFunction* Action = NewObject<UGs2InventoryListOfBigItemAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BigInventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfBigItemAsyncFunction::ListOfBigItem] BigInventory parameter specification is missing."))
        return Action;
    }
    Action->BigInventory = BigInventory;
    return Action;
}

void UGs2InventoryListOfBigItemAsyncFunction::Activate()
{
    TArray<FGs2InventoryBigItemValue> ReturnBigItems;
    FGs2Error ReturnError;

    if (BigInventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfBigItemAsyncFunction::Activate] BigInventory parameter specification is missing."))
        return;
    }
    const auto It = BigInventory.Value->BigItems(
    );
    for (auto v : *It)
    {
        ReturnBigItems.Add(EzBigItemToFGs2InventoryBigItemValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnBigItems, ReturnError);
}