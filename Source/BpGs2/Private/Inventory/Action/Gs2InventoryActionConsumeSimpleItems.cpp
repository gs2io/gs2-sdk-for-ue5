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

#include "Inventory/Action/Gs2InventoryActionConsumeSimpleItems.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryConsumeSimpleItemsAsyncFunction::UGs2InventoryConsumeSimpleItemsAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryConsumeSimpleItemsAsyncFunction* UGs2InventoryConsumeSimpleItemsAsyncFunction::ConsumeSimpleItems(
    UObject* WorldContextObject,
    FGs2InventoryOwnSimpleInventory SimpleInventory,
    TArray<FGs2InventoryConsumeCount> ConsumeCounts
)
{
    UGs2InventoryConsumeSimpleItemsAsyncFunction* Action = NewObject<UGs2InventoryConsumeSimpleItemsAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SimpleInventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryConsumeSimpleItemsAsyncFunction::ConsumeSimpleItems] SimpleInventory parameter specification is missing."))
        return Action;
    }
    Action->SimpleInventory = SimpleInventory;
    Action->ConsumeCounts = ConsumeCounts;
    return Action;
}

void UGs2InventoryConsumeSimpleItemsAsyncFunction::Activate()
{
    if (SimpleInventory.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryConsumeSimpleItemsAsyncFunction] SimpleInventory parameter specification is missing."))
        return;
    }

    auto Future = SimpleInventory.Value->ConsumeSimpleItems(
        [&]
        {
            TArray<Gs2::UE5::Inventory::Model::FEzConsumeCountPtr> r;
            for (auto v : ConsumeCounts)
            {
                r.Add(FGs2InventoryConsumeCountToEzConsumeCount(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        TArray<FGs2InventoryOwnSimpleItem> ReturnSimpleItem;
        for (int i=0; i<Result->Num(); i++)
        {
            FGs2InventoryOwnSimpleItem r;
            r.Value = (*Result)[i];
            ReturnSimpleItem.Add(r);
        }
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSimpleItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        TArray<FGs2InventoryOwnSimpleItem> ReturnSimpleItem;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnSuccess.Broadcast(ReturnSimpleItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}