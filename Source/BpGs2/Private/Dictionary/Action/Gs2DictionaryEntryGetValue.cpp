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

#include "Dictionary/Action/Gs2DictionaryEntryGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryEntryGetValueAsyncFunction::UGs2DictionaryEntryGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryEntryGetValueAsyncFunction* UGs2DictionaryEntryGetValueAsyncFunction::EntryGetValue(
    UObject* WorldContextObject,
    FGs2DictionaryOwnEntry Entry
)
{
    UGs2DictionaryEntryGetValueAsyncFunction* Action = NewObject<UGs2DictionaryEntryGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Entry.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryEntryGetValueAsyncFunction::EntryGetValue] Entry parameter specification is missing."))
        return Action;
    }
    Action->Entry = Entry;
    return Action;
}

void UGs2DictionaryEntryGetValueAsyncFunction::Activate()
{
    auto Future = Entry.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzEntryToFGs2DictionaryEntryValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2DictionaryEntryValue ReturnEntry;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnEntry, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}