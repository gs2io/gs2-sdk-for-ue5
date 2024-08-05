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

#include "Account/Action/Gs2AccountActionAddTakeOverSettingOpenIdConnect.h"
#include "Core/BpGs2Constant.h"

UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction::UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction* UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction::AddTakeOverSettingOpenIdConnect(
    UObject* WorldContextObject,
    FGs2AccountOwnTakeOver TakeOver,
    int32 Type,
    FString IdToken
)
{
    UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction* Action = NewObject<UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (TakeOver.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction::AddTakeOverSettingOpenIdConnect] TakeOver parameter specification is missing."))
        return Action;
    }
    Action->TakeOver = TakeOver;
    Action->Type = Type;
    Action->IdToken = IdToken;
    return Action;
}

void UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction::Activate()
{
    if (TakeOver.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAddTakeOverSettingOpenIdConnectAsyncFunction] TakeOver parameter specification is missing."))
        return;
    }

    auto Future = TakeOver.Value->AddTakeOverSettingOpenIdConnect(
        IdToken
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