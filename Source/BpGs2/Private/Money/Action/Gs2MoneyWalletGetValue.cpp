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

#include "Money/Action/Gs2MoneyWalletGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2MoneyWalletGetValueAsyncFunction::UGs2MoneyWalletGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2MoneyWalletGetValueAsyncFunction* UGs2MoneyWalletGetValueAsyncFunction::WalletGetValue(
    UObject* WorldContextObject,
    FGs2MoneyOwnWallet Wallet
)
{
    UGs2MoneyWalletGetValueAsyncFunction* Action = NewObject<UGs2MoneyWalletGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Wallet.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MoneyWalletGetValueAsyncFunction::WalletGetValue] Wallet parameter specification is missing."))
        return Action;
    }
    Action->Wallet = Wallet;
    return Action;
}

void UGs2MoneyWalletGetValueAsyncFunction::Activate()
{
    auto Future = Wallet.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzWalletToFGs2MoneyWalletValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2MoneyWalletValue ReturnWallet;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnWallet, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}