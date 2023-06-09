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

#include "Idle/Action/Gs2IdleStatusGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2IdleStatusGetValueAsyncFunction::UGs2IdleStatusGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2IdleStatusGetValueAsyncFunction* UGs2IdleStatusGetValueAsyncFunction::StatusGetValue(
    UObject* WorldContextObject,
    FGs2IdleOwnStatus Status
)
{
    UGs2IdleStatusGetValueAsyncFunction* Action = NewObject<UGs2IdleStatusGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2IdleStatusGetValueAsyncFunction::StatusGetValue] Status parameter specification is missing."))
        return Action;
    }
    Action->Status = Status;
    return Action;
}

void UGs2IdleStatusGetValueAsyncFunction::Activate()
{
    auto Future = Status.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzStatusToFGs2IdleStatusValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2IdleStatusValue ReturnStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}