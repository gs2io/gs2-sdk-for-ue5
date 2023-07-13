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

#include "LoginReward/Action/Gs2LoginRewardBonusModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2LoginRewardBonusModelGetValueAsyncFunction::UGs2LoginRewardBonusModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LoginRewardBonusModelGetValueAsyncFunction* UGs2LoginRewardBonusModelGetValueAsyncFunction::BonusModelGetValue(
    UObject* WorldContextObject,
    FGs2LoginRewardBonusModel BonusModel
)
{
    UGs2LoginRewardBonusModelGetValueAsyncFunction* Action = NewObject<UGs2LoginRewardBonusModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BonusModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardBonusModelGetValueAsyncFunction::BonusModelGetValue] BonusModel parameter specification is missing."))
        return Action;
    }
    Action->BonusModel = BonusModel;
    return Action;
}

void UGs2LoginRewardBonusModelGetValueAsyncFunction::Activate()
{
    auto Future = BonusModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBonusModelToFGs2LoginRewardBonusModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2LoginRewardBonusModelValue ReturnBonusModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBonusModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}