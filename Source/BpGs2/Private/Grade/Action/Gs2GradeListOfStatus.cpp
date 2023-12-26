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

#include "Grade/Action/Gs2GradeListOfStatus.h"
#include "Grade/Model/Gs2GradeStatus.h"
#include "Core/BpGs2Constant.h"

UGs2GradeListOfStatusAsyncFunction::UGs2GradeListOfStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2GradeListOfStatusAsyncFunction* UGs2GradeListOfStatusAsyncFunction::ListOfStatus(
    UObject* WorldContextObject,
    FGs2GradeOwnUser User,
    FString GradeName
)
{
    UGs2GradeListOfStatusAsyncFunction* Action = NewObject<UGs2GradeListOfStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeListOfStatusAsyncFunction::ListOfStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->GradeName = GradeName;
    return Action;
}

void UGs2GradeListOfStatusAsyncFunction::Activate()
{
    TArray<FGs2GradeStatusValue> ReturnStatuses;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeListOfStatusAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Statuses(
        GradeName
    );
    for (auto v : *It)
    {
        ReturnStatuses.Add(EzStatusToFGs2GradeStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnStatuses, ReturnError);
}