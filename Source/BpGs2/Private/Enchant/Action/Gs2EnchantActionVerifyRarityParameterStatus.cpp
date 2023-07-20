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

#include "Enchant/Action/Gs2EnchantActionVerifyRarityParameterStatus.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantVerifyRarityParameterStatusAsyncFunction::UGs2EnchantVerifyRarityParameterStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantVerifyRarityParameterStatusAsyncFunction* UGs2EnchantVerifyRarityParameterStatusAsyncFunction::VerifyRarityParameterStatus(
    UObject* WorldContextObject,
    FGs2EnchantOwnRarityParameterStatus RarityParameterStatus,
    FString VerifyType,
    FString ParameterValueName,
    int32 ParameterCount
)
{
    UGs2EnchantVerifyRarityParameterStatusAsyncFunction* Action = NewObject<UGs2EnchantVerifyRarityParameterStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RarityParameterStatus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantVerifyRarityParameterStatusAsyncFunction::VerifyRarityParameterStatus] RarityParameterStatus parameter specification is missing."))
        return Action;
    }
    Action->RarityParameterStatus = RarityParameterStatus;
    Action->VerifyType = VerifyType;
    Action->ParameterValueName = ParameterValueName;
    Action->ParameterCount = ParameterCount;
    return Action;
}

void UGs2EnchantVerifyRarityParameterStatusAsyncFunction::Activate()
{
    if (RarityParameterStatus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantVerifyRarityParameterStatusAsyncFunction] RarityParameterStatus parameter specification is missing."))
        return;
    }

    auto Future = RarityParameterStatus.Value->VerifyRarityParameterStatus(
        VerifyType,
        ParameterValueName,
        ParameterCount
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2EnchantOwnRarityParameterStatus ReturnRarityParameterStatus;
        ReturnRarityParameterStatus.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnRarityParameterStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2EnchantOwnRarityParameterStatus ReturnRarityParameterStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRarityParameterStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}