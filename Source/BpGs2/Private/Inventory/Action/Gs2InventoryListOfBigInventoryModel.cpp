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

#include "Inventory/Action/Gs2InventoryListOfBigInventoryModel.h"
#include "Inventory/Model/Gs2InventoryBigInventoryModel.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryListOfBigInventoryModelAsyncFunction::UGs2InventoryListOfBigInventoryModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryListOfBigInventoryModelAsyncFunction* UGs2InventoryListOfBigInventoryModelAsyncFunction::ListOfBigInventoryModel(
    UObject* WorldContextObject,
    FGs2InventoryNamespace Namespace
)
{
    UGs2InventoryListOfBigInventoryModelAsyncFunction* Action = NewObject<UGs2InventoryListOfBigInventoryModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfBigInventoryModelAsyncFunction::ListOfBigInventoryModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2InventoryListOfBigInventoryModelAsyncFunction::Activate()
{
    TArray<FGs2InventoryBigInventoryModelValue> ReturnBigInventoryModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryListOfBigInventoryModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->BigInventoryModels(
    );
    for (auto v : *It)
    {
        ReturnBigInventoryModels.Add(EzBigInventoryModelToFGs2InventoryBigInventoryModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnBigInventoryModels, ReturnError);
}