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

#include "Quest/Action/Gs2QuestListOfQuestModel.h"
#include "Quest/Model/Gs2QuestQuestModel.h"
#include "Core/BpGs2Constant.h"

UGs2QuestListOfQuestModelAsyncFunction::UGs2QuestListOfQuestModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestListOfQuestModelAsyncFunction* UGs2QuestListOfQuestModelAsyncFunction::ListOfQuestModel(
    UObject* WorldContextObject,
    FGs2QuestQuestGroupModel QuestGroupModel
)
{
    UGs2QuestListOfQuestModelAsyncFunction* Action = NewObject<UGs2QuestListOfQuestModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (QuestGroupModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestListOfQuestModelAsyncFunction::ListOfQuestModel] QuestGroupModel parameter specification is missing."))
        return Action;
    }
    Action->QuestGroupModel = QuestGroupModel;
    return Action;
}

void UGs2QuestListOfQuestModelAsyncFunction::Activate()
{
    TArray<FGs2QuestQuestModelValue> ReturnQuestModels;
    FGs2Error ReturnError;
    const auto It = QuestGroupModel.Value->QuestModels(
    );
    for (auto v : *It)
    {
        ReturnQuestModels.Add(EzQuestModelToFGs2QuestQuestModelValue(v));
    }
    OnSuccess.Broadcast(ReturnQuestModels, ReturnError);
}