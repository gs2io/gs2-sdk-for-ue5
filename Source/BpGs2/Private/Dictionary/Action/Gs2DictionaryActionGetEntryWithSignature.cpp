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

#include "Dictionary/Action/Gs2DictionaryActionGetEntryWithSignature.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryGetEntryWithSignatureAsyncFunction::UGs2DictionaryGetEntryWithSignatureAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryGetEntryWithSignatureAsyncFunction* UGs2DictionaryGetEntryWithSignatureAsyncFunction::GetEntryWithSignature(
    UObject* WorldContextObject,
    FGs2DictionaryOwnEntry Entry,
    FString KeyId
)
{
    UGs2DictionaryGetEntryWithSignatureAsyncFunction* Action = NewObject<UGs2DictionaryGetEntryWithSignatureAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Entry.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryGetEntryWithSignatureAsyncFunction::GetEntryWithSignature] Entry parameter specification is missing."))
        return Action;
    }
    Action->Entry = Entry;
    Action->KeyId = KeyId;
    return Action;
}

void UGs2DictionaryGetEntryWithSignatureAsyncFunction::Activate()
{
    if (Entry.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryGetEntryWithSignatureAsyncFunction] Entry parameter specification is missing."))
        return;
    }

    auto Future = Entry.Value->GetEntryWithSignature(
        KeyId
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2DictionaryOwnEntry ReturnEntry;
        ReturnEntry.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnEntry, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2DictionaryOwnEntry ReturnEntry;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnEntry, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}