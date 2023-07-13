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

#include "LoginReward/Action/Gs2LoginRewardActionReceive.h"
#include "Core/BpGs2Constant.h"

UGs2LoginRewardReceiveAsyncFunction::UGs2LoginRewardReceiveAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LoginRewardReceiveAsyncFunction* UGs2LoginRewardReceiveAsyncFunction::Receive(
    UObject* WorldContextObject,
    FGs2LoginRewardOwnBonus Bonus,
    FString BonusModelName,
    TArray<FGs2LoginRewardConfig> Config
)
{
    UGs2LoginRewardReceiveAsyncFunction* Action = NewObject<UGs2LoginRewardReceiveAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Bonus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardReceiveAsyncFunction::Receive] Bonus parameter specification is missing."))
        return Action;
    }
    Action->Bonus = Bonus;
    Action->BonusModelName = BonusModelName;
    Action->Config = Config;
    return Action;
}

void UGs2LoginRewardReceiveAsyncFunction::Activate()
{
    if (Bonus.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardReceiveAsyncFunction] Bonus parameter specification is missing."))
        return;
    }

    auto Future = Bonus.Value->Receive(
        BonusModelName,
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
        FGs2LoginRewardOwnBonus ReturnBonus;
        ReturnBonus.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnBonus, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2LoginRewardOwnBonus ReturnBonus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBonus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}