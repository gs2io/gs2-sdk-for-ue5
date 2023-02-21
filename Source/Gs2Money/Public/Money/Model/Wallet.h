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
#include "WalletDetail.h"

namespace Gs2::Money::Model
{
    class GS2MONEY_API FWallet final : public TSharedFromThis<FWallet>
    {
        TOptional<FString> WalletIdValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> SlotValue;
        TOptional<int32> PaidValue;
        TOptional<int32> FreeValue;
        TSharedPtr<TArray<TSharedPtr<FWalletDetail>>> DetailValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FWallet();
        FWallet(
            const FWallet& From
        );
        ~FWallet() = default;

        TSharedPtr<FWallet> WithWalletId(const TOptional<FString> WalletId);
        TSharedPtr<FWallet> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FWallet> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FWallet> WithPaid(const TOptional<int32> Paid);
        TSharedPtr<FWallet> WithFree(const TOptional<int32> Free);
        TSharedPtr<FWallet> WithDetail(const TSharedPtr<TArray<TSharedPtr<FWalletDetail>>> Detail);
        TSharedPtr<FWallet> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FWallet> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetWalletId() const;
        TOptional<FString> GetUserId() const;
        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;
        TOptional<int32> GetPaid() const;
        FString GetPaidString() const;
        TOptional<int32> GetFree() const;
        FString GetFreeString() const;
        TSharedPtr<TArray<TSharedPtr<FWalletDetail>>> GetDetail() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

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