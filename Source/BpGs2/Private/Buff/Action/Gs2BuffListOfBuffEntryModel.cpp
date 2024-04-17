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

#include "Buff/Action/Gs2BuffListOfBuffEntryModel.h"
#include "Buff/Model/Gs2BuffBuffEntryModel.h"
#include "Core/BpGs2Constant.h"

UGs2BuffListOfBuffEntryModelAsyncFunction::UGs2BuffListOfBuffEntryModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2BuffListOfBuffEntryModelAsyncFunction* UGs2BuffListOfBuffEntryModelAsyncFunction::ListOfBuffEntryModel(
    UObject* WorldContextObject,
    FGs2BuffNamespace Namespace
)
{
    UGs2BuffListOfBuffEntryModelAsyncFunction* Action = NewObject<UGs2BuffListOfBuffEntryModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffListOfBuffEntryModelAsyncFunction::ListOfBuffEntryModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2BuffListOfBuffEntryModelAsyncFunction::Activate()
{
    TArray<FGs2BuffBuffEntryModelValue> ReturnBuffEntryModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffListOfBuffEntryModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->BuffEntryModels(
    );
    for (auto v : *It)
    {
        ReturnBuffEntryModels.Add(EzBuffEntryModelToFGs2BuffBuffEntryModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnBuffEntryModels, ReturnError);
}