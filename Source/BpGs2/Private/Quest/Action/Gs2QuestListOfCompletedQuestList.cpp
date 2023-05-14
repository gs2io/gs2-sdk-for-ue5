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

#include "Quest/Action/Gs2QuestListOfCompletedQuestList.h"
#include "Quest/Model/Gs2QuestCompletedQuestList.h"
#include "Core/BpGs2Constant.h"

UGs2QuestListOfCompletedQuestListAsyncFunction::UGs2QuestListOfCompletedQuestListAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2QuestListOfCompletedQuestListAsyncFunction* UGs2QuestListOfCompletedQuestListAsyncFunction::ListOfCompletedQuestList(
    UObject* WorldContextObject,
    FGs2QuestOwnUser User
)
{
    UGs2QuestListOfCompletedQuestListAsyncFunction* Action = NewObject<UGs2QuestListOfCompletedQuestListAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2QuestListOfCompletedQuestListAsyncFunction::ListOfCompletedQuestList] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2QuestListOfCompletedQuestListAsyncFunction::Activate()
{
    TArray<FGs2QuestCompletedQuestListValue> ReturnCompletedQuestList;
    FGs2Error ReturnError;
    const auto It = User.Value->CompletedQuestLists(
    );
    for (auto v : *It)
    {
        ReturnCompletedQuestList.Add(EzCompletedQuestListToFGs2QuestCompletedQuestListValue(v.Current()));
    }
    OnSuccess.Broadcast(ReturnCompletedQuestList, ReturnError);
}