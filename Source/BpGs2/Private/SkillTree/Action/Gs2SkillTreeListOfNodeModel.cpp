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

#include "SkillTree/Action/Gs2SkillTreeListOfNodeModel.h"
#include "SkillTree/Model/Gs2SkillTreeNodeModel.h"
#include "Core/BpGs2Constant.h"

UGs2SkillTreeListOfNodeModelAsyncFunction::UGs2SkillTreeListOfNodeModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SkillTreeListOfNodeModelAsyncFunction* UGs2SkillTreeListOfNodeModelAsyncFunction::ListOfNodeModel(
    UObject* WorldContextObject,
    FGs2SkillTreeNamespace Namespace
)
{
    UGs2SkillTreeListOfNodeModelAsyncFunction* Action = NewObject<UGs2SkillTreeListOfNodeModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeListOfNodeModelAsyncFunction::ListOfNodeModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2SkillTreeListOfNodeModelAsyncFunction::Activate()
{
    TArray<FGs2SkillTreeNodeModelValue> ReturnNodeModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeListOfNodeModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->NodeModels(
    );
    for (auto v : *It)
    {
        ReturnNodeModels.Add(EzNodeModelToFGs2SkillTreeNodeModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnNodeModels, ReturnError);
}