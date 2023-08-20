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

#include "BpGs2/Public/Inventory/Model/Gs2InventoryBigInventoryModel.h"
#include "BpGs2/Public/Inventory/Model/Gs2InventoryBigItemModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Inventory/Model/Gs2InventoryBigItemModel.h"
#include "Core/BpGs2Constant.h"

FGs2InventoryBigItemModel UGs2InventoryBigInventoryModelFunctionLibrary::BigItemModel(
    FGs2InventoryBigInventoryModel BigInventoryModel,
    FString ItemName
)
{
    FGs2InventoryBigItemModel Return;
    if (BigInventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryBigInventoryModelFunctionLibrary::BigItemModel] BigInventoryModel parameter specification is missing."))
        return Return;
    }
    if (ItemName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryBigInventoryModelFunctionLibrary::BigItemModel] ItemName parameter specification is missing."))
        return Return;
    }
    Return.Value = BigInventoryModel.Value->BigItemModel(
        ItemName
    );
    return Return;
}