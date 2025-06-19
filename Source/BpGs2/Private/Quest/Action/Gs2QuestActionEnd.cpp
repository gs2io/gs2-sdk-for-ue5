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
    FGs2QuestOwnProgress Progress,
    bool IsComplete,
    TArray<FGs2QuestReward> Rewards,
    TArray<FGs2QuestConfig> Config
)
{
    UGs2QuestEndAsyncFunction* Action = NewObject<UGs2QuestEndAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestEndAsyncFunction::End] Progress parameter specification is missing."))
        return Action;
    }
    Action->Progress = Progress;
    Action->Rewards = Rewards;
    Action->IsComplete = IsComplete;
    Action->Config = Config;
    return Action;
}

void UGs2QuestEndAsyncFunction::Activate()
{
    if (Progress.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestEndAsyncFunction] Progress parameter specification is missing."))
        return;
    }

    auto Future = Progress.Value->End(
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