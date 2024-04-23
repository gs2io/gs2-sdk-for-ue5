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

#include "Version/Action/Gs2VersionActionAccept.h"
#include "Core/BpGs2Constant.h"

UGs2VersionAcceptAsyncFunction::UGs2VersionAcceptAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2VersionAcceptAsyncFunction* UGs2VersionAcceptAsyncFunction::Accept(
    UObject* WorldContextObject,
    FGs2VersionOwnAcceptVersion AcceptVersion,
    FGs2VersionVersion Version
)
{
    UGs2VersionAcceptAsyncFunction* Action = NewObject<UGs2VersionAcceptAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (AcceptVersion.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionAcceptAsyncFunction::Accept] AcceptVersion parameter specification is missing."))
        return Action;
    }
    Action->AcceptVersion = AcceptVersion;
    Action->Version = Version;
    return Action;
}

void UGs2VersionAcceptAsyncFunction::Activate()
{
    if (AcceptVersion.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2VersionAcceptAsyncFunction] AcceptVersion parameter specification is missing."))
        return;
    }

    auto Future = AcceptVersion.Value->Accept(
        FGs2VersionVersionToEzVersion(Version)
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2VersionOwnAcceptVersion ReturnAcceptVersion;
        ReturnAcceptVersion.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnAcceptVersion, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2VersionOwnAcceptVersion ReturnAcceptVersion;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAcceptVersion, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}