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

#include "Exchange/Action/Gs2ExchangeRateModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ExchangeRateModelGetValueAsyncFunction::UGs2ExchangeRateModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExchangeRateModelGetValueAsyncFunction* UGs2ExchangeRateModelGetValueAsyncFunction::RateModelGetValue(
    UObject* WorldContextObject,
    FGs2ExchangeRateModel RateModel
)
{
    UGs2ExchangeRateModelGetValueAsyncFunction* Action = NewObject<UGs2ExchangeRateModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RateModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeRateModelGetValueAsyncFunction::RateModelGetValue] RateModel parameter specification is missing."))
        return Action;
    }
    Action->RateModel = RateModel;
    return Action;
}

void UGs2ExchangeRateModelGetValueAsyncFunction::Activate()
{
    auto Future = RateModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzRateModelToFGs2ExchangeRateModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ExchangeRateModelValue ReturnRateModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRateModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}