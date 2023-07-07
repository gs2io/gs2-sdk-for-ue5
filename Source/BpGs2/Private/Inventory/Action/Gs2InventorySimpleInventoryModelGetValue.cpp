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

#include "Inventory/Action/Gs2InventorySimpleInventoryModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2InventorySimpleInventoryModelGetValueAsyncFunction::UGs2InventorySimpleInventoryModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventorySimpleInventoryModelGetValueAsyncFunction* UGs2InventorySimpleInventoryModelGetValueAsyncFunction::SimpleInventoryModelGetValue(
    UObject* WorldContextObject,
    FGs2InventorySimpleInventoryModel SimpleInventoryModel
)
{
    UGs2InventorySimpleInventoryModelGetValueAsyncFunction* Action = NewObject<UGs2InventorySimpleInventoryModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SimpleInventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventorySimpleInventoryModelGetValueAsyncFunction::SimpleInventoryModelGetValue] SimpleInventoryModel parameter specification is missing."))
        return Action;
    }
    Action->SimpleInventoryModel = SimpleInventoryModel;
    return Action;
}

void UGs2InventorySimpleInventoryModelGetValueAsyncFunction::Activate()
{
    auto Future = SimpleInventoryModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSimpleInventoryModelToFGs2InventorySimpleInventoryModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2InventorySimpleInventoryModelValue ReturnSimpleInventoryModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSimpleInventoryModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}