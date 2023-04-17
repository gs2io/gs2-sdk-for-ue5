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

#include "Quest/Action/Gs2QuestActionEnd.h"
#include "Core/BpGs2Constant.h"

UGs2QuestEndAsyncFunction::UGs2QuestEndAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestEndAsyncFunction* UGs2QuestEndAsyncFunction::End(
    UObject* WorldContextObject,
    FGs2QuestOwnUser User,
    bool IsComplete,
    TArray<FGs2QuestReward> Rewards,
    TArray<FGs2QuestConfig> Config
)
{
    UGs2QuestEndAsyncFunction* Action = NewObject<UGs2QuestEndAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestEndAsyncFunction::End] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->Rewards = Rewards;
    Action->IsComplete = IsComplete;
    Action->Config = Config;
    return Action;
}

void UGs2QuestEndAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestEndAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->End(
        IsComplete,
        [&]
        {
            TArray<Gs2::UE5::Quest::Model::FEzRewardPtr> r;
            for (auto v : Rewards)
            {
                r.Add(FGs2QuestRewardToEzReward(v));
            }
            return r;
        }(),
        [&]
        {
            TArray<Gs2::UE5::Quest::Model::FEzConfigPtr> r;
            for (auto v : Config)
            {
                r.Add(FGs2QuestConfigToEzConfig(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2QuestOwnProgress ReturnProgress;
        ReturnProgress.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnProgress, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2QuestOwnProgress ReturnProgress;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnProgress, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}