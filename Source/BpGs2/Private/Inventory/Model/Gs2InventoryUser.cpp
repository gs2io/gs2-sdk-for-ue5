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

#include "Inventory/Model/Gs2InventoryUser.h"
#include "Inventory/Domain/EzGs2Inventory.h"
#include "Inventory/Model/Gs2InventoryInventory.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Inventory/Model/Gs2InventoryInventory.h"
#include "Inventory/Model/Gs2InventorySimpleInventory.h"
#include "Inventory/Model/Gs2InventoryBigInventory.h"
#include "Core/BpGs2Constant.h"

FGs2InventoryOwnInventory UGs2InventoryUserFunctionLibrary::OwnInventory(
    FGs2InventoryOwnUser User,
    FString InventoryName
)
{
    FGs2InventoryOwnInventory Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryUserFunctionLibrary::OwnInventory] User parameter specification is missing."))
        return Return;
    }
    if (InventoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryUserFunctionLibrary::OwnInventory] InventoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Inventory(
        InventoryName
    );
    return Return;
}

FGs2InventoryOwnSimpleInventory UGs2InventoryUserFunctionLibrary::OwnSimpleInventory(
    FGs2InventoryOwnUser User,
    FString InventoryName
)
{
    FGs2InventoryOwnSimpleInventory Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryUserFunctionLibrary::OwnSimpleInventory] User parameter specification is missing."))
        return Return;
    }
    if (InventoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryUserFunctionLibrary::OwnSimpleInventory] InventoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->SimpleInventory(
        InventoryName
    );
    return Return;
}

FGs2InventoryOwnBigInventory UGs2InventoryUserFunctionLibrary::OwnBigInventory(
    FGs2InventoryOwnUser User,
    FString InventoryName
)
{
    FGs2InventoryOwnBigInventory Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryUserFunctionLibrary::OwnBigInventory] User parameter specification is missing."))
        return Return;
    }
    if (InventoryName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryUserFunctionLibrary::OwnBigInventory] InventoryName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->BigInventory(
        InventoryName
    );
    return Return;
}