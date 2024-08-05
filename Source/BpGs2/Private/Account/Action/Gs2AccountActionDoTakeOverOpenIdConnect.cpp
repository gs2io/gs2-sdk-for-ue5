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

#include "Account/Action/Gs2AccountActionDoTakeOverOpenIdConnect.h"
#include "Core/BpGs2Constant.h"

UGs2AccountDoTakeOverOpenIdConnectAsyncFunction::UGs2AccountDoTakeOverOpenIdConnectAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountDoTakeOverOpenIdConnectAsyncFunction* UGs2AccountDoTakeOverOpenIdConnectAsyncFunction::DoTakeOverOpenIdConnect(
    UObject* WorldContextObject,
    FGs2AccountNamespace Namespace,
    int64 Type,
    FString IdToken
)
{
    UGs2AccountDoTakeOverOpenIdConnectAsyncFunction* Action = NewObject<UGs2AccountDoTakeOverOpenIdConnectAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountDoTakeOverOpenIdConnectAsyncFunction::DoTakeOverOpenIdConnect] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    Action->Type = Type;
    Action->IdToken = IdToken;
    return Action;
}

void UGs2AccountDoTakeOverOpenIdConnectAsyncFunction::Activate()
{
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountDoTakeOverOpenIdConnectAsyncFunction] Namespace parameter specification is missing."))
        return;
    }

    auto Future = Namespace.Value->DoTakeOverOpenIdConnect(
        Type,
        IdToken
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2AccountAccount ReturnAccount;
        ReturnAccount.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnAccount, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2AccountAccount ReturnAccount;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAccount, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}