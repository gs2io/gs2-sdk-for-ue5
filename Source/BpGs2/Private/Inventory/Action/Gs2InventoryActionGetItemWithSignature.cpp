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

#include "Inventory/Action/Gs2InventoryActionGetItemWithSignature.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryGetItemWithSignatureAsyncFunction::UGs2InventoryGetItemWithSignatureAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryGetItemWithSignatureAsyncFunction* UGs2InventoryGetItemWithSignatureAsyncFunction::GetItemWithSignature(
    UObject* WorldContextObject,
    FGs2InventoryOwnItemSet ItemSet,
    FString KeyId
)
{
    UGs2InventoryGetItemWithSignatureAsyncFunction* Action = NewObject<UGs2InventoryGetItemWithSignatureAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (ItemSet.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryGetItemWithSignatureAsyncFunction::GetItemWithSignature] ItemSet parameter specification is missing."))
        return Action;
    }
    Action->ItemSet = ItemSet;
    Action->KeyId = KeyId;
    return Action;
}

void UGs2InventoryGetItemWithSignatureAsyncFunction::Activate()
{
    if (ItemSet.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryGetItemWithSignatureAsyncFunction] ItemSet parameter specification is missing."))
        return;
    }

    auto Future = ItemSet.Value->GetItemWithSignature(
        KeyId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2InventoryOwnItemSet ReturnItemSet;
        ReturnItemSet.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnItemSet, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2InventoryOwnItemSet ReturnItemSet;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnSuccess.Broadcast(ReturnItemSet, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}