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

#include "LoginReward/Action/Gs2LoginRewardActionMissedReceive.h"
#include "Core/BpGs2Constant.h"

UGs2LoginRewardMissedReceiveAsyncFunction::UGs2LoginRewardMissedReceiveAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LoginRewardMissedReceiveAsyncFunction* UGs2LoginRewardMissedReceiveAsyncFunction::MissedReceive(
    UObject* WorldContextObject,
    FGs2LoginRewardOwnBonus Bonus,
    FString BonusModelName,
    int32 StepNumber,
    TArray<FGs2LoginRewardConfig> Config
)
{
    UGs2LoginRewardMissedReceiveAsyncFunction* Action = NewObject<UGs2LoginRewardMissedReceiveAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Bonus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardMissedReceiveAsyncFunction::MissedReceive] Bonus parameter specification is missing."))
        return Action;
    }
    Action->Bonus = Bonus;
    Action->BonusModelName = BonusModelName;
    Action->StepNumber = StepNumber;
    Action->Config = Config;
    return Action;
}

void UGs2LoginRewardMissedReceiveAsyncFunction::Activate()
{
    if (Bonus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardMissedReceiveAsyncFunction] Bonus parameter specification is missing."))
        return;
    }

    auto Future = Bonus.Value->MissedReceive(
        BonusModelName,
        StepNumber,
        [&]
        {
            TArray<Gs2::UE5::LoginReward::Model::FEzConfigPtr> r;
            for (auto v : Config)
            {
                r.Add(FGs2LoginRewardConfigToEzConfig(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}