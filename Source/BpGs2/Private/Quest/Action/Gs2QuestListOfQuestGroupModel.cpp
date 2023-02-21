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

#include "Quest/Action/Gs2QuestListOfQuestGroupModel.h"
#include "Quest/Model/Gs2QuestQuestGroupModel.h"
#include "Core/BpGs2Constant.h"

UGs2QuestListOfQuestGroupModelAsyncFunction::UGs2QuestListOfQuestGroupModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestListOfQuestGroupModelAsyncFunction* UGs2QuestListOfQuestGroupModelAsyncFunction::ListOfQuestGroupModel(
    UObject* WorldContextObject,
    FGs2QuestNamespace Namespace
)
{
    UGs2QuestListOfQuestGroupModelAsyncFunction* Action = NewObject<UGs2QuestListOfQuestGroupModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestListOfQuestGroupModelAsyncFunction::ListOfQuestGroupModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2QuestListOfQuestGroupModelAsyncFunction::Activate()
{
    TArray<FGs2QuestQuestGroupModelValue> ReturnQuestGroupModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->QuestGroupModels(
    );
    for (auto v : *It)
    {
        ReturnQuestGroupModels.Add(EzQuestGroupModelToFGs2QuestQuestGroupModelValue(v));
    }
    OnSuccess.Broadcast(ReturnQuestGroupModels, ReturnError);
}