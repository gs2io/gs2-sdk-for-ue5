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

#include "Stamina/Action/Gs2StaminaStaminaGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2StaminaStaminaGetValueAsyncFunction::UGs2StaminaStaminaGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2StaminaStaminaGetValueAsyncFunction* UGs2StaminaStaminaGetValueAsyncFunction::StaminaGetValue(
    UObject* WorldContextObject,
    FGs2StaminaOwnStamina Stamina
)
{
    UGs2StaminaStaminaGetValueAsyncFunction* Action = NewObject<UGs2StaminaStaminaGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Stamina.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaStaminaGetValueAsyncFunction::StaminaGetValue] Stamina parameter specification is missing."))
        return Action;
    }
    Action->Stamina = Stamina;
    return Action;
}

void UGs2StaminaStaminaGetValueAsyncFunction::Activate()
{
    auto Future = Stamina.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzStaminaToFGs2StaminaStaminaValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2StaminaStaminaValue ReturnStamina;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnStamina, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}