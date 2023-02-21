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

#include "Account/Action/Gs2AccountActionAuthentication.h"
#include "Core/BpGs2Constant.h"

UGs2AccountAuthenticationAsyncFunction::UGs2AccountAuthenticationAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountAuthenticationAsyncFunction* UGs2AccountAuthenticationAsyncFunction::Authentication(
    UObject* WorldContextObject,
    FGs2AccountAccount Account,
    FString KeyId,
    FString Password
)
{
    UGs2AccountAuthenticationAsyncFunction* Action = NewObject<UGs2AccountAuthenticationAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAuthenticationAsyncFunction::Authentication] Account parameter specification is missing."))
        return Action;
    }
    Action->Account = Account;
    Action->KeyId = KeyId;
    Action->Password = Password;
    return Action;
}

void UGs2AccountAuthenticationAsyncFunction::Activate()
{
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAuthenticationAsyncFunction] Account parameter specification is missing."))
        return;
    }

    auto Future = Account.Value->Authentication(
        KeyId,
        Password
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