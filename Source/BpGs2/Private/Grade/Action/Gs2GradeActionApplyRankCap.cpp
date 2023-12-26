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

#include "Grade/Action/Gs2GradeActionApplyRankCap.h"
#include "Core/BpGs2Constant.h"

UGs2GradeApplyRankCapAsyncFunction::UGs2GradeApplyRankCapAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2GradeApplyRankCapAsyncFunction* UGs2GradeApplyRankCapAsyncFunction::ApplyRankCap(
    UObject* WorldContextObject,
    FGs2GradeOwnStatus Status
)
{
    UGs2GradeApplyRankCapAsyncFunction* Action = NewObject<UGs2GradeApplyRankCapAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeApplyRankCapAsyncFunction::ApplyRankCap] Status parameter specification is missing."))
        return Action;
    }
    Action->Status = Status;
    return Action;
}

void UGs2GradeApplyRankCapAsyncFunction::Activate()
{
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeApplyRankCapAsyncFunction] Status parameter specification is missing."))
        return;
    }

    auto Future = Status.Value->ApplyRankCap(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2GradeOwnStatus ReturnStatus;
        ReturnStatus.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2GradeOwnStatus ReturnStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}