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

#include "Account/Action/Gs2AccountTakeOverGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2AccountTakeOverGetValueAsyncFunction::UGs2AccountTakeOverGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountTakeOverGetValueAsyncFunction* UGs2AccountTakeOverGetValueAsyncFunction::TakeOverGetValue(
    UObject* WorldContextObject,
    FGs2AccountOwnTakeOver TakeOver
)
{
    UGs2AccountTakeOverGetValueAsyncFunction* Action = NewObject<UGs2AccountTakeOverGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (TakeOver.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountTakeOverGetValueAsyncFunction::TakeOverGetValue] TakeOver parameter specification is missing."))
        return Action;
    }
    Action->TakeOver = TakeOver;
    return Action;
}

void UGs2AccountTakeOverGetValueAsyncFunction::Activate()
{
    auto Future = TakeOver.Value->Model();
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzTakeOverToFGs2AccountTakeOverValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2AccountTakeOverValue ReturnTakeOver;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTakeOver, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}