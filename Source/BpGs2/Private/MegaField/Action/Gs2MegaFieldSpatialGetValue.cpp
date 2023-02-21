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

#include "MegaField/Action/Gs2MegaFieldSpatialGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MegaFieldSpatialGetValueAsyncFunction::UGs2MegaFieldSpatialGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MegaFieldSpatialGetValueAsyncFunction* UGs2MegaFieldSpatialGetValueAsyncFunction::SpatialGetValue(
    UObject* WorldContextObject,
    FGs2MegaFieldSpatial Spatial
)
{
    UGs2MegaFieldSpatialGetValueAsyncFunction* Action = NewObject<UGs2MegaFieldSpatialGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Spatial.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldSpatialGetValueAsyncFunction::MegaFieldGetValue] Spatial parameter specification is missing."))
        return Action;
    }
    Action->Spatial = Spatial;
    return Action;
}

void UGs2MegaFieldSpatialGetValueAsyncFunction::Activate()
{
    auto Future = Spatial.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSpatialToFGs2MegaFieldSpatialValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MegaFieldSpatialValue ReturnSpatial;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSpatial, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}