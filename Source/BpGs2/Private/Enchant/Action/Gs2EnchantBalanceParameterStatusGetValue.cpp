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

#include "Enchant/Action/Gs2EnchantBalanceParameterStatusGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantBalanceParameterStatusGetValueAsyncFunction::UGs2EnchantBalanceParameterStatusGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantBalanceParameterStatusGetValueAsyncFunction* UGs2EnchantBalanceParameterStatusGetValueAsyncFunction::BalanceParameterStatusGetValue(
    UObject* WorldContextObject,
    FGs2EnchantOwnBalanceParameterStatus BalanceParameterStatus
)
{
    UGs2EnchantBalanceParameterStatusGetValueAsyncFunction* Action = NewObject<UGs2EnchantBalanceParameterStatusGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BalanceParameterStatus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantBalanceParameterStatusGetValueAsyncFunction::BalanceParameterStatusGetValue] BalanceParameterStatus parameter specification is missing."))
        return Action;
    }
    Action->BalanceParameterStatus = BalanceParameterStatus;
    return Action;
}

void UGs2EnchantBalanceParameterStatusGetValueAsyncFunction::Activate()
{
    auto Future = BalanceParameterStatus.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBalanceParameterStatusToFGs2EnchantBalanceParameterStatusValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2EnchantBalanceParameterStatusValue ReturnBalanceParameterStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBalanceParameterStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}