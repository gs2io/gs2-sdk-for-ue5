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

#include "Quest/Action/Gs2QuestQuestGroupModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2QuestQuestGroupModelGetValueAsyncFunction::UGs2QuestQuestGroupModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestQuestGroupModelGetValueAsyncFunction* UGs2QuestQuestGroupModelGetValueAsyncFunction::QuestGroupModelGetValue(
    UObject* WorldContextObject,
    FGs2QuestQuestGroupModel QuestGroupModel
)
{
    UGs2QuestQuestGroupModelGetValueAsyncFunction* Action = NewObject<UGs2QuestQuestGroupModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (QuestGroupModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestQuestGroupModelGetValueAsyncFunction::QuestGroupModelGetValue] QuestGroupModel parameter specification is missing."))
        return Action;
    }
    Action->QuestGroupModel = QuestGroupModel;
    return Action;
}

void UGs2QuestQuestGroupModelGetValueAsyncFunction::Activate()
{
    auto Future = QuestGroupModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzQuestGroupModelToFGs2QuestQuestGroupModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2QuestQuestGroupModelValue ReturnQuestGroupModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnQuestGroupModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}