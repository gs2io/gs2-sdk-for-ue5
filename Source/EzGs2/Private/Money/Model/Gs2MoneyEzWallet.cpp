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

#include "EzGs2/Public/Money/Model/Gs2MoneyEzWallet.h"

namespace Gs2::UE5::Money::Model
{

    TSharedPtr<FEzWallet> FEzWallet::WithSlot(
        const TOptional<int32> Slot
    )
    {
        this->SlotValue = Slot;
        return SharedThis(this);
    }

    TSharedPtr<FEzWallet> FEzWallet::WithPaid(
        const TOptional<int32> Paid
    )
    {
        this->PaidValue = Paid;
        return SharedThis(this);
    }

    TSharedPtr<FEzWallet> FEzWallet::WithFree(
        const TOptional<int32> Free
    )
    {
        this->FreeValue = Free;
        return SharedThis(this);
    }

    TSharedPtr<FEzWallet> FEzWallet::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }
    TOptional<int32> FEzWallet::GetSlot() const
    {
        return SlotValue;
    }

    FString FEzWallet::GetSlotString() const
    {
        if (!SlotValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), SlotValue.GetValue());
    }
    TOptional<int32> FEzWallet::GetPaid() const
    {
        return PaidValue;
    }

    FString FEzWallet::GetPaidString() const
    {
        if (!PaidValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), PaidValue.GetValue());
    }
    TOptional<int32> FEzWallet::GetFree() const
    {
        return FreeValue;
    }

    FString FEzWallet::GetFreeString() const
    {
        if (!FreeValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), FreeValue.GetValue());
    }
    TOptional<int64> FEzWallet::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FEzWallet::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }

    Gs2::Money::Model::FWalletPtr FEzWallet::ToModel() const
    {
        return MakeShared<Gs2::Money::Model::FWallet>()
            ->WithSlot(SlotValue)
            ->WithPaid(PaidValue)
            ->WithFree(FreeValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzWallet> FEzWallet::FromModel(const Gs2::Money::Model::FWalletPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzWallet>()
            ->WithSlot(Model->GetSlot())
            ->WithPaid(Model->GetPaid())
            ->WithFree(Model->GetFree())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}