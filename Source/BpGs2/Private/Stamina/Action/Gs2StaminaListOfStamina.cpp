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

#include "Stamina/Action/Gs2StaminaListOfStamina.h"
#include "Stamina/Model/Gs2StaminaStamina.h"
#include "Core/BpGs2Constant.h"

UGs2StaminaListOfStaminaAsyncFunction::UGs2StaminaListOfStaminaAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2StaminaListOfStaminaAsyncFunction* UGs2StaminaListOfStaminaAsyncFunction::ListOfStamina(
    UObject* WorldContextObject,
    FGs2StaminaOwnUser User
)
{
    UGs2StaminaListOfStaminaAsyncFunction* Action = NewObject<UGs2StaminaListOfStaminaAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaListOfStaminaAsyncFunction::ListOfStamina] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2StaminaListOfStaminaAsyncFunction::Activate()
{
    TArray<FGs2StaminaStaminaValue> ReturnStaminas;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaListOfStaminaAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Staminas(
    );
    for (auto v : *It)
    {
        ReturnStaminas.Add(EzStaminaToFGs2StaminaStaminaValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnStaminas, ReturnError);
}