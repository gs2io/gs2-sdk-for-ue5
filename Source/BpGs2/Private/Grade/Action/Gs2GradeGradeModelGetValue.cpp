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

#include "Grade/Action/Gs2GradeGradeModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2GradeGradeModelGetValueAsyncFunction::UGs2GradeGradeModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2GradeGradeModelGetValueAsyncFunction* UGs2GradeGradeModelGetValueAsyncFunction::GradeModelGetValue(
    UObject* WorldContextObject,
    FGs2GradeGradeModel GradeModel
)
{
    UGs2GradeGradeModelGetValueAsyncFunction* Action = NewObject<UGs2GradeGradeModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (GradeModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2GradeGradeModelGetValueAsyncFunction::GradeModelGetValue] GradeModel parameter specification is missing."))
        return Action;
    }
    Action->GradeModel = GradeModel;
    return Action;
}

void UGs2GradeGradeModelGetValueAsyncFunction::Activate()
{
    auto Future = GradeModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzGradeModelToFGs2GradeGradeModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2GradeGradeModelValue ReturnGradeModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnGradeModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}