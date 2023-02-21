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

#include "Account/Action/Gs2AccountActionUpdateTakeOverSetting.h"
#include "Core/BpGs2Constant.h"

UGs2AccountUpdateTakeOverSettingAsyncFunction::UGs2AccountUpdateTakeOverSettingAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountUpdateTakeOverSettingAsyncFunction* UGs2AccountUpdateTakeOverSettingAsyncFunction::UpdateTakeOverSetting(
    UObject* WorldContextObject,
    FGs2AccountOwnTakeOver TakeOver,
    FString OldPassword,
    FString Password
)
{
    UGs2AccountUpdateTakeOverSettingAsyncFunction* Action = NewObject<UGs2AccountUpdateTakeOverSettingAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (TakeOver.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountUpdateTakeOverSettingAsyncFunction::UpdateTakeOverSetting] TakeOver parameter specification is missing."))
        return Action;
    }
    Action->TakeOver = TakeOver;
    Action->OldPassword = OldPassword;
    Action->Password = Password;
    return Action;
}

void UGs2AccountUpdateTakeOverSettingAsyncFunction::Activate()
{
    if (TakeOver.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountUpdateTakeOverSettingAsyncFunction] TakeOver parameter specification is missing."))
        return;
    }

    auto Future = TakeOver.Value->UpdateTakeOverSetting(
        OldPassword,
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