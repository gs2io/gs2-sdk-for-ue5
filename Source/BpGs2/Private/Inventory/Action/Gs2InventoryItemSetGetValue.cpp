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

#include "Inventory/Action/Gs2InventoryItemSetGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryItemSetGetValueAsyncFunction::UGs2InventoryItemSetGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryItemSetGetValueAsyncFunction* UGs2InventoryItemSetGetValueAsyncFunction::ItemSetGetValue(
    UObject* WorldContextObject,
    FGs2InventoryOwnItemSet ItemSet
)
{
    UGs2InventoryItemSetGetValueAsyncFunction* Action = NewObject<UGs2InventoryItemSetGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (ItemSet.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryItemSetGetValueAsyncFunction::ItemSetGetValue] ItemSet parameter specification is missing."))
        return Action;
    }
    Action->ItemSet = ItemSet;
    return Action;
}

void UGs2InventoryItemSetGetValueAsyncFunction::Activate()
{
    auto Future = ItemSet.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        TArray<FGs2InventoryItemSetValue> ReturnValue;
        for (int i=0; i<Result->Num(); i++)
        {
            ReturnValue.Add(EzItemSetToFGs2InventoryItemSetValue((*Result)[i]));
        }
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        TArray<FGs2InventoryItemSetValue> ReturnArray;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnArray, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}