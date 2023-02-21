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

#include "Account/Action/Gs2AccountActionAddTakeOverSetting.h"
#include "Core/BpGs2Constant.h"

UGs2AccountAddTakeOverSettingAsyncFunction::UGs2AccountAddTakeOverSettingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountAddTakeOverSettingAsyncFunction* UGs2AccountAddTakeOverSettingAsyncFunction::AddTakeOverSetting(
    UObject* WorldContextObject,
    FGs2AccountOwnTakeOver TakeOver,
    int32 Type,
    FString UserIdentifier,
    FString Password
)
{
    UGs2AccountAddTakeOverSettingAsyncFunction* Action = NewObject<UGs2AccountAddTakeOverSettingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (TakeOver.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAddTakeOverSettingAsyncFunction::AddTakeOverSetting] TakeOver parameter specification is missing."))
        return Action;
    }
    Action->TakeOver = TakeOver;
    Action->UserIdentifier = UserIdentifier;
    Action->Password = Password;
    return Action;
}

void UGs2AccountAddTakeOverSettingAsyncFunction::Activate()
{
    if (TakeOver.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAddTakeOverSettingAsyncFunction] TakeOver parameter specification is missing."))
        return;
    }

    auto Future = TakeOver.Value->AddTakeOverSetting(
        UserIdentifier,
        Password
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2AccountOwnTakeOver ReturnTakeOver;
        ReturnTakeOver.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnTakeOver, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2AccountOwnTakeOver ReturnTakeOver;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTakeOver, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}