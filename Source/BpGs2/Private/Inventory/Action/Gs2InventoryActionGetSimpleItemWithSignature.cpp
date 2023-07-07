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

#include "Inventory/Action/Gs2InventoryActionGetSimpleItemWithSignature.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryGetSimpleItemWithSignatureAsyncFunction::UGs2InventoryGetSimpleItemWithSignatureAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryGetSimpleItemWithSignatureAsyncFunction* UGs2InventoryGetSimpleItemWithSignatureAsyncFunction::GetSimpleItemWithSignature(
    UObject* WorldContextObject,
    FGs2InventoryOwnSimpleItem SimpleItem,
    FString KeyId
)
{
    UGs2InventoryGetSimpleItemWithSignatureAsyncFunction* Action = NewObject<UGs2InventoryGetSimpleItemWithSignatureAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SimpleItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryGetSimpleItemWithSignatureAsyncFunction::GetSimpleItemWithSignature] SimpleItem parameter specification is missing."))
        return Action;
    }
    Action->SimpleItem = SimpleItem;
    Action->KeyId = KeyId;
    return Action;
}

void UGs2InventoryGetSimpleItemWithSignatureAsyncFunction::Activate()
{
    if (SimpleItem.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryGetSimpleItemWithSignatureAsyncFunction] SimpleItem parameter specification is missing."))
        return;
    }

    auto Future = SimpleItem.Value->GetSimpleItemWithSignature(
        KeyId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2InventoryOwnSimpleItem ReturnSimpleItem;
        ReturnSimpleItem.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSimpleItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2InventoryOwnSimpleItem ReturnSimpleItem;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSimpleItem, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}