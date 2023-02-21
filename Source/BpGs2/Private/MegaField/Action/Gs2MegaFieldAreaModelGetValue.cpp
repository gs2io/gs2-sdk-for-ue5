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

#include "MegaField/Action/Gs2MegaFieldAreaModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MegaFieldAreaModelGetValueAsyncFunction::UGs2MegaFieldAreaModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MegaFieldAreaModelGetValueAsyncFunction* UGs2MegaFieldAreaModelGetValueAsyncFunction::AreaModelGetValue(
    UObject* WorldContextObject,
    FGs2MegaFieldAreaModel AreaModel
)
{
    UGs2MegaFieldAreaModelGetValueAsyncFunction* Action = NewObject<UGs2MegaFieldAreaModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (AreaModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MegaFieldAreaModelGetValueAsyncFunction::AreaModelGetValue] AreaModel parameter specification is missing."))
        return Action;
    }
    Action->AreaModel = AreaModel;
    return Action;
}

void UGs2MegaFieldAreaModelGetValueAsyncFunction::Activate()
{
    auto Future = AreaModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzAreaModelToFGs2MegaFieldAreaModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MegaFieldAreaModelValue ReturnAreaModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAreaModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}