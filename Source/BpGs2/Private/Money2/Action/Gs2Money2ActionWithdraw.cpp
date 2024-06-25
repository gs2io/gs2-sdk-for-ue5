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

#include "Money2/Action/Gs2Money2ActionWithdraw.h"
#include "Core/BpGs2Constant.h"

UGs2Money2WithdrawAsyncFunction::UGs2Money2WithdrawAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2Money2WithdrawAsyncFunction* UGs2Money2WithdrawAsyncFunction::Withdraw(
    UObject* WorldContextObject,
    FGs2Money2OwnWallet Wallet,
    int32 WithdrawCount,
    bool PaidOnly
)
{
    UGs2Money2WithdrawAsyncFunction* Action = NewObject<UGs2Money2WithdrawAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Wallet.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2WithdrawAsyncFunction::Withdraw] Wallet parameter specification is missing."))
        return Action;
    }
    Action->Wallet = Wallet;
    Action->WithdrawCount = WithdrawCount;
    Action->PaidOnly = PaidOnly;
    return Action;
}

void UGs2Money2WithdrawAsyncFunction::Activate()
{
    if (Wallet.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2WithdrawAsyncFunction] Wallet parameter specification is missing."))
        return;
    }

    auto Future = Wallet.Value->Withdraw(
        WithdrawCount,
        PaidOnly
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2Money2OwnWallet ReturnWallet;
        ReturnWallet.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnWallet, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2Money2OwnWallet ReturnWallet;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnWallet, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}