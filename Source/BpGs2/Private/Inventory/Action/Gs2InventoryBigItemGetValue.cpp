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

#include "Inventory/Action/Gs2InventoryBigItemGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryBigItemGetValueAsyncFunction::UGs2InventoryBigItemGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryBigItemGetValueAsyncFunction* UGs2InventoryBigItemGetValueAsyncFunction::BigItemGetValue(
    UObject* WorldContextObject,
    FGs2InventoryOwnBigItem BigItem
)
{
    UGs2InventoryBigItemGetValueAsyncFunction* Action = NewObject<UGs2InventoryBigItemGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BigItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryBigItemGetValueAsyncFunction::BigItemGetValue] BigItem parameter specification is missing."))
        return Action;
    }
    Action->BigItem = BigItem;
    return Action;
}

void UGs2InventoryBigItemGetValueAsyncFunction::Activate()
{
    auto Future = BigItem.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBigItemToFGs2InventoryBigItemValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2InventoryBigItemValue ReturnBigItem;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBigItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}