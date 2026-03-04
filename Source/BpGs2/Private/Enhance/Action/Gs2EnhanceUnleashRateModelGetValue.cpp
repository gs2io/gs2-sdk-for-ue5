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

#include "Enhance/Action/Gs2EnhanceUnleashRateModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2EnhanceUnleashRateModelGetValueAsyncFunction::UGs2EnhanceUnleashRateModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnhanceUnleashRateModelGetValueAsyncFunction* UGs2EnhanceUnleashRateModelGetValueAsyncFunction::UnleashRateModelGetValue(
    UObject* WorldContextObject,
    FGs2EnhanceUnleashRateModel UnleashRateModel
)
{
    UGs2EnhanceUnleashRateModelGetValueAsyncFunction* Action = NewObject<UGs2EnhanceUnleashRateModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (UnleashRateModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceUnleashRateModelGetValueAsyncFunction::UnleashRateModelGetValue] UnleashRateModel parameter specification is missing."))
        return Action;
    }
    Action->UnleashRateModel = UnleashRateModel;
    return Action;
}

void UGs2EnhanceUnleashRateModelGetValueAsyncFunction::Activate()
{
    auto Future = UnleashRateModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzUnleashRateModelToFGs2EnhanceUnleashRateModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2EnhanceUnleashRateModelValue ReturnUnleashRateModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnUnleashRateModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}