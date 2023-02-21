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
#include "Money/Model/Wallet.h"

namespace Gs2::UE5::Money::Model
{
	class EZGS2_API FEzWallet final : public TSharedFromThis<FEzWallet>
	{
        TOptional<int32> SlotValue;
        TOptional<int32> PaidValue;
        TOptional<int32> FreeValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzWallet> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FEzWallet> WithPaid(const TOptional<int32> Paid);
        TSharedPtr<FEzWallet> WithFree(const TOptional<int32> Free);
        TSharedPtr<FEzWallet> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;

        TOptional<int32> GetPaid() const;
        FString GetPaidString() const;

        TOptional<int32> GetFree() const;
        FString GetFreeString() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Money::Model::FWalletPtr ToModel() const;
        static TSharedPtr<FEzWallet> FromModel(Gs2::Money::Model::FWalletPtr Model);
    };
    typedef TSharedPtr<FEzWallet> FEzWalletPtr;
}