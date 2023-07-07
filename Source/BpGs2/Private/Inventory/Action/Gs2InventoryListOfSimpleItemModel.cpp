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

#include "Inventory/Action/Gs2InventoryListOfSimpleItemModel.h"
#include "Inventory/Model/Gs2InventorySimpleItemModel.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfSimpleItemModelAsyncFunction::UGs2InventoryListOfSimpleItemModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfSimpleItemModelAsyncFunction* UGs2InventoryListOfSimpleItemModelAsyncFunction::ListOfSimpleItemModel(
    UObject* WorldContextObject,
    FGs2InventorySimpleInventoryModel SimpleInventoryModel
)
{
    UGs2InventoryListOfSimpleItemModelAsyncFunction* Action = NewObject<UGs2InventoryListOfSimpleItemModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SimpleInventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfSimpleItemModelAsyncFunction::ListOfSimpleItemModel] SimpleInventoryModel parameter specification is missing."))
        return Action;
    }
    Action->SimpleInventoryModel = SimpleInventoryModel;
    return Action;
}

void UGs2InventoryListOfSimpleItemModelAsyncFunction::Activate()
{
    TArray<FGs2InventorySimpleItemModelValue> ReturnSimpleItemModels;
    FGs2Error ReturnError;

    if (SimpleInventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfSimpleItemModelAsyncFunction::Activate] SimpleInventoryModel parameter specification is missing."))
        return;
    }
    const auto It = SimpleInventoryModel.Value->SimpleItemModels(
    );
    for (auto v : *It)
    {
        ReturnSimpleItemModels.Add(EzSimpleItemModelToFGs2InventorySimpleItemModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnSimpleItemModels, ReturnError);
}