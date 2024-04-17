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

#include "Buff/Action/Gs2BuffBuffEntryModelGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2BuffBuffEntryModelGetValueAsyncFunction::UGs2BuffBuffEntryModelGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2BuffBuffEntryModelGetValueAsyncFunction* UGs2BuffBuffEntryModelGetValueAsyncFunction::BuffEntryModelGetValue(
    UObject* WorldContextObject,
    FGs2BuffBuffEntryModel BuffEntryModel
)
{
    UGs2BuffBuffEntryModelGetValueAsyncFunction* Action = NewObject<UGs2BuffBuffEntryModelGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BuffEntryModel.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2BuffBuffEntryModelGetValueAsyncFunction::BuffEntryModelGetValue] BuffEntryModel parameter specification is missing."))
        return Action;
    }
    Action->BuffEntryModel = BuffEntryModel;
    return Action;
}

void UGs2BuffBuffEntryModelGetValueAsyncFunction::Activate()
{
    auto Future = BuffEntryModel.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBuffEntryModelToFGs2BuffBuffEntryModelValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2BuffBuffEntryModelValue ReturnBuffEntryModel;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBuffEntryModel, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}