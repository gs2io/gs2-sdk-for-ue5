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

#include "Money2/Model/Gs2Money2EzDepositTransaction.h"

namespace Gs2::UE5::Money2::Model
{

    TSharedPtr<FEzDepositTransaction> FEzDepositTransaction::WithPrice(
        const TOptional<double> Price
    )
    {
        this->PriceValue = Price;
        return SharedThis(this);
    }

    TSharedPtr<FEzDepositTransaction> FEzDepositTransaction::WithCurrency(
        const TOptional<FString> Currency
    )
    {
        this->CurrencyValue = Currency;
        return SharedThis(this);
    }

    TSharedPtr<FEzDepositTransaction> FEzDepositTransaction::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<double> FEzDepositTransaction::GetPrice() const
    {
        return PriceValue;
    }

    FString FEzDepositTransaction::GetPriceString() const
    {
        if (!PriceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), PriceValue.GetValue());
    }
    TOptional<FString> FEzDepositTransaction::GetCurrency() const
    {
        return CurrencyValue;
    }
    TOptional<int32> FEzDepositTransaction::GetCount() const
    {
        return CountValue;
    }

    FString FEzDepositTransaction::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    Gs2::Money2::Model::FDepositTransactionPtr FEzDepositTransaction::ToModel() const
    {
        return MakeShared<Gs2::Money2::Model::FDepositTransaction>()
            ->WithPrice(PriceValue)
            ->WithCurrency(CurrencyValue)
            ->WithCount(CountValue);
    }

    TSharedPtr<FEzDepositTransaction> FEzDepositTransaction::FromModel(const Gs2::Money2::Model::FDepositTransactionPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzDepositTransaction>()
            ->WithPrice(Model->GetPrice())
            ->WithCurrency(Model->GetCurrency())
            ->WithCount(Model->GetCount());
    }
}