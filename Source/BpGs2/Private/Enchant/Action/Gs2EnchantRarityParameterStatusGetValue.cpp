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

#include "Enchant/Action/Gs2EnchantRarityParameterStatusGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantRarityParameterStatusGetValueAsyncFunction::UGs2EnchantRarityParameterStatusGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantRarityParameterStatusGetValueAsyncFunction* UGs2EnchantRarityParameterStatusGetValueAsyncFunction::RarityParameterStatusGetValue(
    UObject* WorldContextObject,
    FGs2EnchantOwnRarityParameterStatus RarityParameterStatus
)
{
    UGs2EnchantRarityParameterStatusGetValueAsyncFunction* Action = NewObject<UGs2EnchantRarityParameterStatusGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RarityParameterStatus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantRarityParameterStatusGetValueAsyncFunction::RarityParameterStatusGetValue] RarityParameterStatus parameter specification is missing."))
        return Action;
    }
    Action->RarityParameterStatus = RarityParameterStatus;
    return Action;
}

void UGs2EnchantRarityParameterStatusGetValueAsyncFunction::Activate()
{
    auto Future = RarityParameterStatus.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzRarityParameterStatusToFGs2EnchantRarityParameterStatusValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2EnchantRarityParameterStatusValue ReturnRarityParameterStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRarityParameterStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}