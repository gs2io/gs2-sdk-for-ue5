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

#include "Inventory/Action/Gs2InventoryBigInventoryModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2InventoryBigInventoryModelGetValueAsyncFunction::UGs2InventoryBigInventoryModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2InventoryBigInventoryModelGetValueAsyncFunction* UGs2InventoryBigInventoryModelGetValueAsyncFunction::BigInventoryModelGetValue(
    UObject* WorldContextObject,
    FGs2InventoryBigInventoryModel BigInventoryModel
)
{
    UGs2InventoryBigInventoryModelGetValueAsyncFunction* Action = NewObject<UGs2InventoryBigInventoryModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BigInventoryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2InventoryBigInventoryModelGetValueAsyncFunction::BigInventoryModelGetValue] BigInventoryModel parameter specification is missing."))
        return Action;
    }
    Action->BigInventoryModel = BigInventoryModel;
    return Action;
}

void UGs2InventoryBigInventoryModelGetValueAsyncFunction::Activate()
{
    auto Future = BigInventoryModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBigInventoryModelToFGs2InventoryBigInventoryModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2InventoryBigInventoryModelValue ReturnBigInventoryModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBigInventoryModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}