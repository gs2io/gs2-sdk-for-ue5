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
 *
 * deny overwrite
 */

#include "Quest/Action/Gs2QuestActionStart.h"
#include "Core/BpGs2Constant.h"

UGs2QuestStartAsyncFunction::UGs2QuestStartAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestStartAsyncFunction* UGs2QuestStartAsyncFunction::Start(
    UObject* WorldContextObject,
    FGs2QuestOwnUser User,
    FString QuestGroupName,
    FString QuestName,
    bool Force,
    TArray<FGs2QuestConfig> Config
)
{
    UGs2QuestStartAsyncFunction* Action = NewObject<UGs2QuestStartAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestStartAsyncFunction::Start] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->QuestGroupName = QuestGroupName;
    Action->QuestName = QuestName;
    Action->Force = Force;
    Action->Config = Config;
    return Action;
}

void UGs2QuestStartAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestStartAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->Start(
        QuestGroupName,
        QuestName,
        Force,
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
        FGs2QuestOwnUser ReturnUser;
        ReturnUser.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2QuestOwnUser ReturnUser;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnUser, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}