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

#include "Exchange/Action/Gs2ExchangeIncrementalRateModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2ExchangeIncrementalRateModelGetValueAsyncFunction::UGs2ExchangeIncrementalRateModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExchangeIncrementalRateModelGetValueAsyncFunction* UGs2ExchangeIncrementalRateModelGetValueAsyncFunction::IncrementalRateModelGetValue(
    UObject* WorldContextObject,
    FGs2ExchangeIncrementalRateModel IncrementalRateModel
)
{
    UGs2ExchangeIncrementalRateModelGetValueAsyncFunction* Action = NewObject<UGs2ExchangeIncrementalRateModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (IncrementalRateModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeIncrementalRateModelGetValueAsyncFunction::IncrementalRateModelGetValue] IncrementalRateModel parameter specification is missing."))
        return Action;
    }
    Action->IncrementalRateModel = IncrementalRateModel;
    return Action;
}

void UGs2ExchangeIncrementalRateModelGetValueAsyncFunction::Activate()
{
    auto Future = IncrementalRateModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzIncrementalRateModelToFGs2ExchangeIncrementalRateModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ExchangeIncrementalRateModelValue ReturnIncrementalRateModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnIncrementalRateModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}