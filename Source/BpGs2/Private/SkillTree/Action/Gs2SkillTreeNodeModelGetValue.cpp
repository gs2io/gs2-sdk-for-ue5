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

#include "SkillTree/Action/Gs2SkillTreeNodeModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2SkillTreeNodeModelGetValueAsyncFunction::UGs2SkillTreeNodeModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SkillTreeNodeModelGetValueAsyncFunction* UGs2SkillTreeNodeModelGetValueAsyncFunction::NodeModelGetValue(
    UObject* WorldContextObject,
    FGs2SkillTreeNodeModel NodeModel
)
{
    UGs2SkillTreeNodeModelGetValueAsyncFunction* Action = NewObject<UGs2SkillTreeNodeModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (NodeModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeNodeModelGetValueAsyncFunction::NodeModelGetValue] NodeModel parameter specification is missing."))
        return Action;
    }
    Action->NodeModel = NodeModel;
    return Action;
}

void UGs2SkillTreeNodeModelGetValueAsyncFunction::Activate()
{
    auto Future = NodeModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzNodeModelToFGs2SkillTreeNodeModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2SkillTreeNodeModelValue ReturnNodeModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnNodeModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}