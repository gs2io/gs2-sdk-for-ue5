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

#include "Dictionary/Action/Gs2DictionaryEntryModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2DictionaryEntryModelGetValueAsyncFunction::UGs2DictionaryEntryModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2DictionaryEntryModelGetValueAsyncFunction* UGs2DictionaryEntryModelGetValueAsyncFunction::EntryModelGetValue(
    UObject* WorldContextObject,
    FGs2DictionaryEntryModel EntryModel
)
{
    UGs2DictionaryEntryModelGetValueAsyncFunction* Action = NewObject<UGs2DictionaryEntryModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (EntryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2DictionaryEntryModelGetValueAsyncFunction::EntryModelGetValue] EntryModel parameter specification is missing."))
        return Action;
    }
    Action->EntryModel = EntryModel;
    return Action;
}

void UGs2DictionaryEntryModelGetValueAsyncFunction::Activate()
{
    auto Future = EntryModel.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzEntryModelToFGs2DictionaryEntryModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2DictionaryEntryModelValue ReturnEntryModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnEntryModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}