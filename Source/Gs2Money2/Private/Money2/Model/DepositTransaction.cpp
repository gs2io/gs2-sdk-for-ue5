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

#include "Money2/Model/DepositTransaction.h"

namespace Gs2::Money2::Model
{
    FDepositTransaction::FDepositTransaction():
        PriceValue(TOptional<double>()),
        CurrencyValue(TOptional<FString>()),
        CountValue(TOptional<int32>()),
        DepositedAtValue(TOptional<int64>())
    {
    }

    FDepositTransaction::FDepositTransaction(
        const FDepositTransaction& From
    ):
        PriceValue(From.PriceValue),
        CurrencyValue(From.CurrencyValue),
        CountValue(From.CountValue),
        DepositedAtValue(From.DepositedAtValue)
    {
    }

    TSharedPtr<FDepositTransaction> FDepositTransaction::WithPrice(
        const TOptional<double> Price
    )
    {
        this->PriceValue = Price;
        return SharedThis(this);
    }

    TSharedPtr<FDepositTransaction> FDepositTransaction::WithCurrency(
        const TOptional<FString> Currency
    )
    {
        this->CurrencyValue = Currency;
        return SharedThis(this);
    }

    TSharedPtr<FDepositTransaction> FDepositTransaction::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FDepositTransaction> FDepositTransaction::WithDepositedAt(
        const TOptional<int64> DepositedAt
    )
    {
        this->DepositedAtValue = DepositedAt;
        return SharedThis(this);
    }
    TOptional<double> FDepositTransaction::GetPrice() const
    {
        return PriceValue;
    }

    FString FDepositTransaction::GetPriceString() const
    {
        if (!PriceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), PriceValue.GetValue());
    }
    TOptional<FString> FDepositTransaction::GetCurrency() const
    {
        return CurrencyValue;
    }
    TOptional<int32> FDepositTransaction::GetCount() const
    {
        return CountValue;
    }

    FString FDepositTransaction::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }
    TOptional<int64> FDepositTransaction::GetDepositedAt() const
    {
        return DepositedAtValue;
    }

    FString FDepositTransaction::GetDepositedAtString() const
    {
        if (!DepositedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DepositedAtValue.GetValue());
    }

    TSharedPtr<FDepositTransaction> FDepositTransaction::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDepositTransaction>()
            ->WithPrice(Data->HasField(ANSI_TO_TCHAR("price")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("price"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithCurrency(Data->HasField(ANSI_TO_TCHAR("currency")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("currency"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCount(Data->HasField(ANSI_TO_TCHAR("count")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("count"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithDepositedAt(Data->HasField(ANSI_TO_TCHAR("depositedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("depositedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FDepositTransaction::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PriceValue.IsSet())
        {
            JsonRootObject->SetNumberField("price", PriceValue.GetValue());
        }
        if (CurrencyValue.IsSet())
        {
            JsonRootObject->SetStringField("currency", CurrencyValue.GetValue());
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField("count", CountValue.GetValue());
        }
        if (DepositedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("depositedAt", FString::Printf(TEXT("%lld"), DepositedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FDepositTransaction::TypeName = "DepositTransaction";
}