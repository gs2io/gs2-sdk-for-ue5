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

#include "Account/Action/Gs2AccountAccountGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2AccountAccountGetValueAsyncFunction::UGs2AccountAccountGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountAccountGetValueAsyncFunction* UGs2AccountAccountGetValueAsyncFunction::AccountGetValue(
    UObject* WorldContextObject,
    FGs2AccountAccount Account
)
{
    UGs2AccountAccountGetValueAsyncFunction* Action = NewObject<UGs2AccountAccountGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountAccountGetValueAsyncFunction::AccountGetValue] Account parameter specification is missing."))
        return Action;
    }
    Action->Account = Account;
    return Action;
}

void UGs2AccountAccountGetValueAsyncFunction::Activate()
{
    auto Future = Account.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzAccountToFGs2AccountAccountValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2AccountAccountValue ReturnAccount;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAccount, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}