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

#include "Inventory/Action/Gs2InventorySimpleItemModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2InventorySimpleItemModelGetValueAsyncFunction::UGs2InventorySimpleItemModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventorySimpleItemModelGetValueAsyncFunction* UGs2InventorySimpleItemModelGetValueAsyncFunction::SimpleItemModelGetValue(
    UObject* WorldContextObject,
    FGs2InventorySimpleItemModel SimpleItemModel
)
{
    UGs2InventorySimpleItemModelGetValueAsyncFunction* Action = NewObject<UGs2InventorySimpleItemModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SimpleItemModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventorySimpleItemModelGetValueAsyncFunction::SimpleItemModelGetValue] SimpleItemModel parameter specification is missing."))
        return Action;
    }
    Action->SimpleItemModel = SimpleItemModel;
    return Action;
}

void UGs2InventorySimpleItemModelGetValueAsyncFunction::Activate()
{
    auto Future = SimpleItemModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSimpleItemModelToFGs2InventorySimpleItemModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2InventorySimpleItemModelValue ReturnSimpleItemModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSimpleItemModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}