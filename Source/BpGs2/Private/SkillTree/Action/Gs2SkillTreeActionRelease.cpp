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

#include "SkillTree/Action/Gs2SkillTreeActionRelease.h"
#include "Core/BpGs2Constant.h"

UGs2SkillTreeReleaseAsyncFunction::UGs2SkillTreeReleaseAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2SkillTreeReleaseAsyncFunction* UGs2SkillTreeReleaseAsyncFunction::Release(
    UObject* WorldContextObject,
    FGs2SkillTreeOwnStatus Status,
    TArray<FString> NodeModelNames
)
{
    UGs2SkillTreeReleaseAsyncFunction* Action = NewObject<UGs2SkillTreeReleaseAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeReleaseAsyncFunction::Release] Status parameter specification is missing."))
        return Action;
    }
    Action->Status = Status;
    Action->NodeModelNames = NodeModelNames;
    return Action;
}

void UGs2SkillTreeReleaseAsyncFunction::Activate()
{
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SkillTreeReleaseAsyncFunction] Status parameter specification is missing."))
        return;
    }

    auto Future = Status.Value->Release(
        NodeModelNames
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2SkillTreeOwnStatus ReturnStatus;
        ReturnStatus.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2SkillTreeOwnStatus ReturnStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}