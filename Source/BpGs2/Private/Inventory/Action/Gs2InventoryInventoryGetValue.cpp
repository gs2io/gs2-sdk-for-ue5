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

#include "Inventory/Action/Gs2InventoryInventoryGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryInventoryGetValueAsyncFunction::UGs2InventoryInventoryGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryInventoryGetValueAsyncFunction* UGs2InventoryInventoryGetValueAsyncFunction::InventoryGetValue(
    UObject* WorldContextObject,
    FGs2InventoryOwnInventory Inventory
)
{
    UGs2InventoryInventoryGetValueAsyncFunction* Action = NewObject<UGs2InventoryInventoryGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Inventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryInventoryGetValueAsyncFunction::InventoryGetValue] Inventory parameter specification is missing."))
        return Action;
    }
    Action->Inventory = Inventory;
    return Action;
}

void UGs2InventoryInventoryGetValueAsyncFunction::Activate()
{
    auto Future = Inventory.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzInventoryToFGs2InventoryInventoryValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2InventoryInventoryValue ReturnInventory;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnInventory, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}