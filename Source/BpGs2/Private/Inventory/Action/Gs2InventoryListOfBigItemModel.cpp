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

#include "Inventory/Action/Gs2InventoryListOfBigItemModel.h"
#include "Inventory/Model/Gs2InventoryBigItemModel.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfBigItemModelAsyncFunction::UGs2InventoryListOfBigItemModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfBigItemModelAsyncFunction* UGs2InventoryListOfBigItemModelAsyncFunction::ListOfBigItemModel(
    UObject* WorldContextObject,
    FGs2InventoryBigInventoryModel BigInventoryModel
)
{
    UGs2InventoryListOfBigItemModelAsyncFunction* Action = NewObject<UGs2InventoryListOfBigItemModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BigInventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfBigItemModelAsyncFunction::ListOfBigItemModel] BigInventoryModel parameter specification is missing."))
        return Action;
    }
    Action->BigInventoryModel = BigInventoryModel;
    return Action;
}

void UGs2InventoryListOfBigItemModelAsyncFunction::Activate()
{
    TArray<FGs2InventoryBigItemModelValue> ReturnBigItemModels;
    FGs2Error ReturnError;

    if (BigInventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfBigItemModelAsyncFunction::Activate] BigInventoryModel parameter specification is missing."))
        return;
    }
    const auto It = BigInventoryModel.Value->BigItemModels(
    );
    for (auto v : *It)
    {
        ReturnBigItemModels.Add(EzBigItemModelToFGs2InventoryBigItemModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnBigItemModels, ReturnError);
}