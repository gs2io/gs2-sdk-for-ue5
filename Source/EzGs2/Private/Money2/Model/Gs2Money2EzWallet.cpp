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

#include "Money2/Model/Gs2Money2EzWallet.h"

namespace Gs2::UE5::Money2::Model
{

    TSharedPtr<FEzWallet> FEzWallet::WithSlot(
        const TOptional<int32> Slot
    )
    {
        this->SlotValue = Slot;
        return SharedThis(this);
    }

    TSharedPtr<FEzWallet> FEzWallet::WithSummary(
        const TSharedPtr<Gs2::UE5::Money2::Model::FEzWalletSummary> Summary
    )
    {
        this->SummaryValue = Summary;
        return SharedThis(this);
    }

    TSharedPtr<FEzWallet> FEzWallet::WithSharedFreeCurrency(
        const TOptional<bool> SharedFreeCurrency
    )
    {
        this->SharedFreeCurrencyValue = SharedFreeCurrency;
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
        return FString::Printf(TEXT("%d"), SlotValue.GetValue());
    }
    TSharedPtr<Gs2::UE5::Money2::Model::FEzWalletSummary> FEzWallet::GetSummary() const
    {
        return SummaryValue;
    }
    TOptional<bool> FEzWallet::GetSharedFreeCurrency() const
    {
        return SharedFreeCurrencyValue;
    }

    FString FEzWallet::GetSharedFreeCurrencyString() const
    {
        if (!SharedFreeCurrencyValue.IsSet())
        {
            return FString("null");
        }
        return FString(SharedFreeCurrencyValue.GetValue() ? "true" : "false");
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

    Gs2::Money2::Model::FWalletPtr FEzWallet::ToModel() const
    {
        return MakeShared<Gs2::Money2::Model::FWallet>()
            ->WithSlot(SlotValue)
            ->WithSummary(SummaryValue == nullptr ? nullptr : SummaryValue->ToModel())
            ->WithSharedFreeCurrency(SharedFreeCurrencyValue)
            ->WithUpdatedAt(UpdatedAtValue);
    }

    TSharedPtr<FEzWallet> FEzWallet::FromModel(const Gs2::Money2::Model::FWalletPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzWallet>()
            ->WithSlot(Model->GetSlot())
            ->WithSummary(Model->GetSummary() != nullptr ? Gs2::UE5::Money2::Model::FEzWalletSummary::FromModel(Model->GetSummary()) : nullptr)
            ->WithSharedFreeCurrency(Model->GetSharedFreeCurrency())
            ->WithUpdatedAt(Model->GetUpdatedAt());
    }
}