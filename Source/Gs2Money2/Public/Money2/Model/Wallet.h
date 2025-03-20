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
#include "Core/Gs2Object.h"
#include "WalletSummary.h"
#include "DepositTransaction.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FWallet final : public FGs2Object, public TSharedFromThis<FWallet>
    {
        TOptional<FString> WalletIdValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> SlotValue;
        TSharedPtr<FWalletSummary> SummaryValue;
        TSharedPtr<TArray<TSharedPtr<FDepositTransaction>>> DepositTransactionsValue;
        TOptional<bool> SharedFreeCurrencyValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FWallet();
        FWallet(
            const FWallet& From
        );
        virtual ~FWallet() override = default;

        TSharedPtr<FWallet> WithWalletId(const TOptional<FString> WalletId);
        TSharedPtr<FWallet> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FWallet> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FWallet> WithSummary(const TSharedPtr<FWalletSummary> Summary);
        TSharedPtr<FWallet> WithDepositTransactions(const TSharedPtr<TArray<TSharedPtr<FDepositTransaction>>> DepositTransactions);
        TSharedPtr<FWallet> WithSharedFreeCurrency(const TOptional<bool> SharedFreeCurrency);
        TSharedPtr<FWallet> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FWallet> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FWallet> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetWalletId() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;
        TSharedPtr<FWalletSummary> GetSummary() const;
        TSharedPtr<TArray<TSharedPtr<FDepositTransaction>>> GetDepositTransactions() const;
        TOptional<bool> GetSharedFreeCurrency() const;
        FString GetSharedFreeCurrencyString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);
        static TOptional<FString> GetSlotFromGrn(const FString Grn);

        static TSharedPtr<FWallet> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FWallet, ESPMode::ThreadSafe> FWalletPtr;
}