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
 *
 * deny overwrite
 */

#include "News/Action/Gs2NewsActionGetContentsUrl.h"
#include "Core/BpGs2Constant.h"

UGs2NewsGetContentsUrlAsyncFunction::UGs2NewsGetContentsUrlAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2NewsGetContentsUrlAsyncFunction* UGs2NewsGetContentsUrlAsyncFunction::GetContentsUrl(
    UObject* WorldContextObject,
    FGs2NewsOwnUser User
)
{
    UGs2NewsGetContentsUrlAsyncFunction* Action = NewObject<UGs2NewsGetContentsUrlAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2NewsGetContentsUrlAsyncFunction::GetContentsUrl] News parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2NewsGetContentsUrlAsyncFunction::Activate()
{
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2NewsGetContentsUrlAsyncFunction] User parameter specification is missing."))
        return;
    }

    auto Future = User.Value->News()->GetContentsUrl(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        TArray<FGs2NewsOwnSetCookieRequestEntry> ReturnSetCookieRequestEntry;
        for (auto v : *Result)
        {
            FGs2NewsOwnSetCookieRequestEntry v2;
            v2.Value = v;
            ReturnSetCookieRequestEntry.Add(v2);
        }
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnSetCookieRequestEntry, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        TArray<FGs2NewsOwnSetCookieRequestEntry> ReturnSetCookieRequestEntry;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSetCookieRequestEntry, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}