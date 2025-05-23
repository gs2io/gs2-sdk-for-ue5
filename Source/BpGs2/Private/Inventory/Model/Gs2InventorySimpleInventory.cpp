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

#include "Inventory/Model/Gs2InventorySimpleInventory.h"
#include "Inventory/Domain/EzGs2Inventory.h"
#include "Inventory/Model/Gs2InventorySimpleItem.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Inventory/Model/Gs2InventorySimpleItem.h"
#include "Core/BpGs2Constant.h"

FGs2InventoryOwnSimpleItem UGs2InventorySimpleInventoryFunctionLibrary::OwnSimpleItem(
    FGs2InventoryOwnSimpleInventory SimpleInventory,
    FString ItemName
)
{
    FGs2InventoryOwnSimpleItem Return;
    if (SimpleInventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventorySimpleInventoryFunctionLibrary::OwnSimpleItem] SimpleInventory parameter specification is missing."))
        return Return;
    }
    if (ItemName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventorySimpleInventoryFunctionLibrary::OwnSimpleItem] ItemName parameter specification is missing."))
        return Return;
    }
    Return.Value = SimpleInventory.Value->SimpleItem(
        ItemName
    );
    return Return;
}