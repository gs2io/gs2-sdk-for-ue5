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

#include "Account/Action/Gs2AccountPlatformIdGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2AccountPlatformIdGetValueAsyncFunction::UGs2AccountPlatformIdGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountPlatformIdGetValueAsyncFunction* UGs2AccountPlatformIdGetValueAsyncFunction::PlatformIdGetValue(
    UObject* WorldContextObject,
    FGs2AccountOwnPlatformId PlatformId
)
{
    UGs2AccountPlatformIdGetValueAsyncFunction* Action = NewObject<UGs2AccountPlatformIdGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (PlatformId.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountPlatformIdGetValueAsyncFunction::PlatformIdGetValue] PlatformId parameter specification is missing."))
        return Action;
    }
    Action->PlatformId = PlatformId;
    return Action;
}

void UGs2AccountPlatformIdGetValueAsyncFunction::Activate()
{
    auto Future = PlatformId.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzPlatformIdToFGs2AccountPlatformIdValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2AccountPlatformIdValue ReturnPlatformId;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnPlatformId, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}