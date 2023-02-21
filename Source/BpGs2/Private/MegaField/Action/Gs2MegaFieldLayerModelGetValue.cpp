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

#include "MegaField/Action/Gs2MegaFieldLayerModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MegaFieldLayerModelGetValueAsyncFunction::UGs2MegaFieldLayerModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MegaFieldLayerModelGetValueAsyncFunction* UGs2MegaFieldLayerModelGetValueAsyncFunction::LayerModelGetValue(
    UObject* WorldContextObject,
    FGs2MegaFieldLayerModel LayerModel
)
{
    UGs2MegaFieldLayerModelGetValueAsyncFunction* Action = NewObject<UGs2MegaFieldLayerModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (LayerModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldLayerModelGetValueAsyncFunction::LayerModelGetValue] LayerModel parameter specification is missing."))
        return Action;
    }
    Action->LayerModel = LayerModel;
    return Action;
}

void UGs2MegaFieldLayerModelGetValueAsyncFunction::Activate()
{
    auto Future = LayerModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzLayerModelToFGs2MegaFieldLayerModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MegaFieldLayerModelValue ReturnLayerModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnLayerModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}