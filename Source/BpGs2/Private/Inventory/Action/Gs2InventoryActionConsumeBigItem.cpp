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

#include "Inventory/Action/Gs2InventoryActionConsumeBigItem.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryConsumeBigItemAsyncFunction::UGs2InventoryConsumeBigItemAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryConsumeBigItemAsyncFunction* UGs2InventoryConsumeBigItemAsyncFunction::ConsumeBigItem(
    UObject* WorldContextObject,
    FGs2InventoryOwnBigItem BigItem,
    FString ConsumeCount
)
{
    UGs2InventoryConsumeBigItemAsyncFunction* Action = NewObject<UGs2InventoryConsumeBigItemAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BigItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryConsumeBigItemAsyncFunction::ConsumeBigItem] BigItem parameter specification is missing."))
        return Action;
    }
    Action->BigItem = BigItem;
    Action->ConsumeCount = ConsumeCount;
    return Action;
}

void UGs2InventoryConsumeBigItemAsyncFunction::Activate()
{
    if (BigItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryConsumeBigItemAsyncFunction] BigItem parameter specification is missing."))
        return;
    }

    auto Future = BigItem.Value->ConsumeBigItem(
        ConsumeCount
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2InventoryOwnBigItem ReturnBigItem;
        ReturnBigItem.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnBigItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2InventoryOwnBigItem ReturnBigItem;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBigItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}