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

#include "News/Action/Gs2NewsSetCookieRequestEntryGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2NewsSetCookieRequestEntryGetValueAsyncFunction::UGs2NewsSetCookieRequestEntryGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2NewsSetCookieRequestEntryGetValueAsyncFunction* UGs2NewsSetCookieRequestEntryGetValueAsyncFunction::SetCookieRequestEntryGetValue(
    UObject* WorldContextObject,
    FGs2NewsOwnSetCookieRequestEntry SetCookieRequestEntry
)
{
    UGs2NewsSetCookieRequestEntryGetValueAsyncFunction* Action = NewObject<UGs2NewsSetCookieRequestEntryGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (SetCookieRequestEntry.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2NewsSetCookieRequestEntryGetValueAsyncFunction::NewsGetValue] SetCookieRequestEntry parameter specification is missing."))
        return Action;
    }
    Action->SetCookieRequestEntry = SetCookieRequestEntry;
    return Action;
}

void UGs2NewsSetCookieRequestEntryGetValueAsyncFunction::Activate()
{
    auto Future = SetCookieRequestEntry.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzSetCookieRequestEntryToFGs2NewsSetCookieRequestEntryValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2NewsSetCookieRequestEntryValue ReturnSetCookieRequestEntry;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnSetCookieRequestEntry, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}