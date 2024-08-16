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

#include "Inventory/Model/Gs2InventoryInventory.h"
#include "Inventory/Domain/EzGs2Inventory.h"
#include "Inventory/Model/Gs2InventoryItemSet.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Inventory/Model/Gs2InventoryItemSet.h"
#include "Core/BpGs2Constant.h"

FGs2InventoryOwnItemSet UGs2InventoryInventoryFunctionLibrary::OwnItemSet(
    FGs2InventoryOwnInventory Inventory,
    FString ItemName,
    FString ItemSetName
)
{
    FGs2InventoryOwnItemSet Return;
    if (Inventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryInventoryFunctionLibrary::OwnItemSet] Inventory parameter specification is missing."))
        return Return;
    }
    if (ItemName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryInventoryFunctionLibrary::OwnItemSet] ItemName parameter specification is missing."))
        return Return;
    }
    Return.Value = Inventory.Value->ItemSet(
        ItemName,
        ItemSetName
    );
    return Return;
}