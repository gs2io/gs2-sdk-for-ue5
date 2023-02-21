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

#include "Limit/Action/Gs2LimitLimitModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2LimitLimitModelGetValueAsyncFunction::UGs2LimitLimitModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LimitLimitModelGetValueAsyncFunction* UGs2LimitLimitModelGetValueAsyncFunction::LimitModelGetValue(
    UObject* WorldContextObject,
    FGs2LimitLimitModel LimitModel
)
{
    UGs2LimitLimitModelGetValueAsyncFunction* Action = NewObject<UGs2LimitLimitModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (LimitModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitLimitModelGetValueAsyncFunction::LimitModelGetValue] LimitModel parameter specification is missing."))
        return Action;
    }
    Action->LimitModel = LimitModel;
    return Action;
}

void UGs2LimitLimitModelGetValueAsyncFunction::Activate()
{
    auto Future = LimitModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzLimitModelToFGs2LimitLimitModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2LimitLimitModelValue ReturnLimitModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnLimitModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}