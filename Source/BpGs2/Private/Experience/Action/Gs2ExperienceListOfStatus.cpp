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

#include "Experience/Action/Gs2ExperienceListOfStatus.h"
#include "Experience/Model/Gs2ExperienceStatus.h"
#include "Core/BpGs2Constant.h"

UGs2ExperienceListOfStatusAsyncFunction::UGs2ExperienceListOfStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExperienceListOfStatusAsyncFunction* UGs2ExperienceListOfStatusAsyncFunction::ListOfStatus(
    UObject* WorldContextObject,
    FGs2ExperienceOwnUser User,
    FString ExperienceName
)
{
    UGs2ExperienceListOfStatusAsyncFunction* Action = NewObject<UGs2ExperienceListOfStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceListOfStatusAsyncFunction::ListOfStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->ExperienceName = ExperienceName;
    return Action;
}

void UGs2ExperienceListOfStatusAsyncFunction::Activate()
{
    TArray<FGs2ExperienceStatusValue> ReturnStatuses;
    FGs2Error ReturnError;
    const auto It = User.Value->Statuses(
        ExperienceName
    );
    for (auto v : *It)
    {
        ReturnStatuses.Add(EzStatusToFGs2ExperienceStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnStatuses, ReturnError);
}