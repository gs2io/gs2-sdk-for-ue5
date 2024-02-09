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

#include "Quest/Action/Gs2QuestQuestModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2QuestQuestModelGetValueAsyncFunction::UGs2QuestQuestModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestQuestModelGetValueAsyncFunction* UGs2QuestQuestModelGetValueAsyncFunction::QuestModelGetValue(
    UObject* WorldContextObject,
    FGs2QuestQuestModel QuestModel
)
{
    UGs2QuestQuestModelGetValueAsyncFunction* Action = NewObject<UGs2QuestQuestModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (QuestModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestQuestModelGetValueAsyncFunction::QuestModelGetValue] QuestModel parameter specification is missing."))
        return Action;
    }
    Action->QuestModel = QuestModel;
    return Action;
}

void UGs2QuestQuestModelGetValueAsyncFunction::Activate()
{
    auto Future = QuestModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzQuestModelToFGs2QuestQuestModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2QuestQuestModelValue ReturnQuestModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnQuestModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}