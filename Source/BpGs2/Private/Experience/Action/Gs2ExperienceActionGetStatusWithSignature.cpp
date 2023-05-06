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

#include "Experience/Action/Gs2ExperienceActionGetStatusWithSignature.h"
#include "Core/BpGs2Constant.h"

UGs2ExperienceGetStatusWithSignatureAsyncFunction::UGs2ExperienceGetStatusWithSignatureAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExperienceGetStatusWithSignatureAsyncFunction* UGs2ExperienceGetStatusWithSignatureAsyncFunction::GetStatusWithSignature(
    UObject* WorldContextObject,
    FGs2ExperienceOwnStatus Status,
    FString KeyId
)
{
    UGs2ExperienceGetStatusWithSignatureAsyncFunction* Action = NewObject<UGs2ExperienceGetStatusWithSignatureAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceGetStatusWithSignatureAsyncFunction::GetStatusWithSignature] Status parameter specification is missing."))
        return Action;
    }
    Action->Status = Status;
    Action->KeyId = KeyId;
    return Action;
}

void UGs2ExperienceGetStatusWithSignatureAsyncFunction::Activate()
{
    if (Status.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceGetStatusWithSignatureAsyncFunction] Status parameter specification is missing."))
        return;
    }

    auto Future = Status.Value->GetStatusWithSignature(
        KeyId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2ExperienceOwnStatus ReturnStatus;
        ReturnStatus.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2ExperienceOwnStatus ReturnStatus;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnStatus, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}