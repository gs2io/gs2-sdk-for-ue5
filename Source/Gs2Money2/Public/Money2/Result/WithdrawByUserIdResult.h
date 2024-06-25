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

#pragma once

#include "CoreMinimal.h"
#include "../Model/Wallet.h"
#include "../Model/DepositTransaction.h"

namespace Gs2::Money2::Result
{
    class GS2MONEY2_API FWithdrawByUserIdResult final : public TSharedFromThis<FWithdrawByUserIdResult>
    {
        TSharedPtr<Model::FWallet> ItemValue;
        TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> WithdrawTransactionsValue;
        
    public:
        
        FWithdrawByUserIdResult();
        FWithdrawByUserIdResult(
            const FWithdrawByUserIdResult& From
        );
        ~FWithdrawByUserIdResult() = default;

        TSharedPtr<FWithdrawByUserIdResult> WithItem(const TSharedPtr<Model::FWallet> Item);
        TSharedPtr<FWithdrawByUserIdResult> WithWithdrawTransactions(const TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> WithdrawTransactions);

        TSharedPtr<Model::FWallet> GetItem() const;
        TSharedPtr<TArray<TSharedPtr<Model::FDepositTransaction>>> GetWithdrawTransactions() const;

        static TSharedPtr<FWithdrawByUserIdResult> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FWithdrawByUserIdResult, ESPMode::ThreadSafe> FWithdrawByUserIdResultPtr;
}