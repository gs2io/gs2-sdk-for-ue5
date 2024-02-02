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

#include "Enchant/Action/Gs2EnchantBalanceParameterModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantBalanceParameterModelGetValueAsyncFunction::UGs2EnchantBalanceParameterModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantBalanceParameterModelGetValueAsyncFunction* UGs2EnchantBalanceParameterModelGetValueAsyncFunction::BalanceParameterModelGetValue(
    UObject* WorldContextObject,
    FGs2EnchantBalanceParameterModel BalanceParameterModel
)
{
    UGs2EnchantBalanceParameterModelGetValueAsyncFunction* Action = NewObject<UGs2EnchantBalanceParameterModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BalanceParameterModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantBalanceParameterModelGetValueAsyncFunction::BalanceParameterModelGetValue] BalanceParameterModel parameter specification is missing."))
        return Action;
    }
    Action->BalanceParameterModel = BalanceParameterModel;
    return Action;
}

void UGs2EnchantBalanceParameterModelGetValueAsyncFunction::Activate()
{
    auto Future = BalanceParameterModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBalanceParameterModelToFGs2EnchantBalanceParameterModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2EnchantBalanceParameterModelValue ReturnBalanceParameterModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBalanceParameterModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}