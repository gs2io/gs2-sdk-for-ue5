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

#include "Version/Action/Gs2VersionAcceptVersionGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2VersionAcceptVersionGetValueAsyncFunction::UGs2VersionAcceptVersionGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2VersionAcceptVersionGetValueAsyncFunction* UGs2VersionAcceptVersionGetValueAsyncFunction::AcceptVersionGetValue(
    UObject* WorldContextObject,
    FGs2VersionOwnAcceptVersion AcceptVersion
)
{
    UGs2VersionAcceptVersionGetValueAsyncFunction* Action = NewObject<UGs2VersionAcceptVersionGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (AcceptVersion.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionAcceptVersionGetValueAsyncFunction::AcceptVersionGetValue] AcceptVersion parameter specification is missing."))
        return Action;
    }
    Action->AcceptVersion = AcceptVersion;
    return Action;
}

void UGs2VersionAcceptVersionGetValueAsyncFunction::Activate()
{
    auto Future = AcceptVersion.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzAcceptVersionToFGs2VersionAcceptVersionValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2VersionAcceptVersionValue ReturnAcceptVersion;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAcceptVersion, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}