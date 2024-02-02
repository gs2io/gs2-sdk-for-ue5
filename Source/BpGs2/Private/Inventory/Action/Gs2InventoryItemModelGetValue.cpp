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

#include "Inventory/Action/Gs2InventoryItemModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryItemModelGetValueAsyncFunction::UGs2InventoryItemModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryItemModelGetValueAsyncFunction* UGs2InventoryItemModelGetValueAsyncFunction::ItemModelGetValue(
    UObject* WorldContextObject,
    FGs2InventoryItemModel ItemModel
)
{
    UGs2InventoryItemModelGetValueAsyncFunction* Action = NewObject<UGs2InventoryItemModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (ItemModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryItemModelGetValueAsyncFunction::ItemModelGetValue] ItemModel parameter specification is missing."))
        return Action;
    }
    Action->ItemModel = ItemModel;
    return Action;
}

void UGs2InventoryItemModelGetValueAsyncFunction::Activate()
{
    auto Future = ItemModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzItemModelToFGs2InventoryItemModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2InventoryItemModelValue ReturnItemModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnItemModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}