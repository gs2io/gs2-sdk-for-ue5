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

#include "Inventory/Action/Gs2InventoryListOfInventory.h"
#include "Inventory/Model/Gs2InventoryInventory.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfInventoryAsyncFunction::UGs2InventoryListOfInventoryAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfInventoryAsyncFunction* UGs2InventoryListOfInventoryAsyncFunction::ListOfInventory(
    UObject* WorldContextObject,
    FGs2InventoryOwnUser User
)
{
    UGs2InventoryListOfInventoryAsyncFunction* Action = NewObject<UGs2InventoryListOfInventoryAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfInventoryAsyncFunction::ListOfInventory] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2InventoryListOfInventoryAsyncFunction::Activate()
{
    TArray<FGs2InventoryInventoryValue> ReturnInventories;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfInventoryAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Inventories(
    );
    for (auto v : *It)
    {
        ReturnInventories.Add(EzInventoryToFGs2InventoryInventoryValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnInventories, ReturnError);
}