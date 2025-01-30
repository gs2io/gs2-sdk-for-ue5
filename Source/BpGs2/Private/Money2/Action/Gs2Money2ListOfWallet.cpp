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

#include "Money2/Action/Gs2Money2ListOfWallet.h"
#include "Money2/Model/Gs2Money2Wallet.h"
#include "Core/BpGs2Constant.h"

UGs2Money2ListOfWalletAsyncFunction::UGs2Money2ListOfWalletAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2Money2ListOfWalletAsyncFunction* UGs2Money2ListOfWalletAsyncFunction::ListOfWallet(
    UObject* WorldContextObject,
    FGs2Money2OwnUser User
)
{
    UGs2Money2ListOfWalletAsyncFunction* Action = NewObject<UGs2Money2ListOfWalletAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2ListOfWalletAsyncFunction::ListOfWallet] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2Money2ListOfWalletAsyncFunction::Activate()
{
    TArray<FGs2Money2WalletValue> ReturnWallets;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2Money2ListOfWalletAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->Wallets(
    );
    for (auto v : *It)
    {
        ReturnWallets.Add(EzWalletToFGs2Money2WalletValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnWallets, ReturnError);
}