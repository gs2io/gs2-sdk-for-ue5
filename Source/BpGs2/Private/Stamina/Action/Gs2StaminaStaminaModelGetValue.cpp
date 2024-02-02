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

#include "Stamina/Action/Gs2StaminaStaminaModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2StaminaStaminaModelGetValueAsyncFunction::UGs2StaminaStaminaModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2StaminaStaminaModelGetValueAsyncFunction* UGs2StaminaStaminaModelGetValueAsyncFunction::StaminaModelGetValue(
    UObject* WorldContextObject,
    FGs2StaminaStaminaModel StaminaModel
)
{
    UGs2StaminaStaminaModelGetValueAsyncFunction* Action = NewObject<UGs2StaminaStaminaModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (StaminaModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2StaminaStaminaModelGetValueAsyncFunction::StaminaModelGetValue] StaminaModel parameter specification is missing."))
        return Action;
    }
    Action->StaminaModel = StaminaModel;
    return Action;
}

void UGs2StaminaStaminaModelGetValueAsyncFunction::Activate()
{
    auto Future = StaminaModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzStaminaModelToFGs2StaminaStaminaModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2StaminaStaminaModelValue ReturnStaminaModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnStaminaModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}