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

#include "Account/Action/Gs2AccountActionRequestDeletion.h"
#include "Core/BpGs2Constant.h"

UGs2AccountRequestDeletionAsyncFunction::UGs2AccountRequestDeletionAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountRequestDeletionAsyncFunction* UGs2AccountRequestDeletionAsyncFunction::RequestDeletion(
    UObject* WorldContextObject,
    FGs2AccountOwnAccount Account
)
{
    UGs2AccountRequestDeletionAsyncFunction* Action = NewObject<UGs2AccountRequestDeletionAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountRequestDeletionAsyncFunction::RequestDeletion] Account parameter specification is missing."))
        return Action;
    }
    Action->Account = Account;
    return Action;
}

void UGs2AccountRequestDeletionAsyncFunction::Activate()
{
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountRequestDeletionAsyncFunction] Account parameter specification is missing."))
        return;
    }

    auto Future = Account.Value->RequestDeletion(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2AccountOwnAccount ReturnAccount;
        ReturnAccount.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnAccount, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2AccountOwnAccount ReturnAccount;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnAccount, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}