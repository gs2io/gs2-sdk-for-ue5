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

#include "Dictionary/Action/Gs2DictionaryListOfEntryModel.h"
#include "Dictionary/Model/Gs2DictionaryEntryModel.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryListOfEntryModelAsyncFunction::UGs2DictionaryListOfEntryModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryListOfEntryModelAsyncFunction* UGs2DictionaryListOfEntryModelAsyncFunction::ListOfEntryModel(
    UObject* WorldContextObject,
    FGs2DictionaryNamespace Namespace
)
{
    UGs2DictionaryListOfEntryModelAsyncFunction* Action = NewObject<UGs2DictionaryListOfEntryModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryListOfEntryModelAsyncFunction::ListOfEntryModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2DictionaryListOfEntryModelAsyncFunction::Activate()
{
    TArray<FGs2DictionaryEntryModelValue> ReturnEntryModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->EntryModels(
    );
    for (auto v : *It)
    {
        ReturnEntryModels.Add(EzEntryModelToFGs2DictionaryEntryModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnEntryModels, ReturnError);
}