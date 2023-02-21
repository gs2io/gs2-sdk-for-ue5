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

#include "Dictionary/Action/Gs2DictionaryListOfEntry.h"
#include "Dictionary/Model/Gs2DictionaryEntry.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryListOfEntryAsyncFunction::UGs2DictionaryListOfEntryAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryListOfEntryAsyncFunction* UGs2DictionaryListOfEntryAsyncFunction::ListOfEntry(
    UObject* WorldContextObject,
    FGs2DictionaryOwnUser User
)
{
    UGs2DictionaryListOfEntryAsyncFunction* Action = NewObject<UGs2DictionaryListOfEntryAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryListOfEntryAsyncFunction::ListOfEntry] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2DictionaryListOfEntryAsyncFunction::Activate()
{
    TArray<FGs2DictionaryEntryValue> ReturnEntries;
    FGs2Error ReturnError;
    const auto It = User.Value->Entries(
    );
    for (auto v : *It)
    {
        ReturnEntries.Add(EzEntryToFGs2DictionaryEntryValue(v));
    }
    OnSuccess.Broadcast(ReturnEntries, ReturnError);
}