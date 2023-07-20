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

#include "Enchant/Action/Gs2EnchantRarityParameterModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantRarityParameterModelGetValueAsyncFunction::UGs2EnchantRarityParameterModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantRarityParameterModelGetValueAsyncFunction* UGs2EnchantRarityParameterModelGetValueAsyncFunction::RarityParameterModelGetValue(
    UObject* WorldContextObject,
    FGs2EnchantRarityParameterModel RarityParameterModel
)
{
    UGs2EnchantRarityParameterModelGetValueAsyncFunction* Action = NewObject<UGs2EnchantRarityParameterModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (RarityParameterModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantRarityParameterModelGetValueAsyncFunction::RarityParameterModelGetValue] RarityParameterModel parameter specification is missing."))
        return Action;
    }
    Action->RarityParameterModel = RarityParameterModel;
    return Action;
}

void UGs2EnchantRarityParameterModelGetValueAsyncFunction::Activate()
{
    auto Future = RarityParameterModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzRarityParameterModelToFGs2EnchantRarityParameterModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2EnchantRarityParameterModelValue ReturnRarityParameterModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnRarityParameterModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}