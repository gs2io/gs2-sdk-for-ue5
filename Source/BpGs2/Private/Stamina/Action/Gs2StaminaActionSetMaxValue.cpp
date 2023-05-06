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

#include "Stamina/Action/Gs2StaminaActionSetMaxValue.h"
#include "Core/BpGs2Constant.h"

UGs2StaminaSetMaxValueAsyncFunction::UGs2StaminaSetMaxValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2StaminaSetMaxValueAsyncFunction* UGs2StaminaSetMaxValueAsyncFunction::SetMaxValue(
    UObject* WorldContextObject,
    FGs2StaminaOwnStamina Stamina,
    FString KeyId,
    FString SignedStatusBody,
    FString SignedStatusSignature
)
{
    UGs2StaminaSetMaxValueAsyncFunction* Action = NewObject<UGs2StaminaSetMaxValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Stamina.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaSetMaxValueAsyncFunction::SetMaxValue] Stamina parameter specification is missing."))
        return Action;
    }
    Action->Stamina = Stamina;
    Action->KeyId = KeyId;
    Action->SignedStatusBody = SignedStatusBody;
    Action->SignedStatusSignature = SignedStatusSignature;
    return Action;
}

void UGs2StaminaSetMaxValueAsyncFunction::Activate()
{
    if (Stamina.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaSetMaxValueAsyncFunction] Stamina parameter specification is missing."))
        return;
    }

    auto Future = Stamina.Value->SetMaxValue(
        KeyId,
        SignedStatusBody,
        SignedStatusSignature
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2StaminaOwnStamina ReturnStamina;
        ReturnStamina.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnStamina, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2StaminaOwnStamina ReturnStamina;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnStamina, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}