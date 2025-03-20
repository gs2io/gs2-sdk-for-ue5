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

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FDepositTransaction final : public FGs2Object, public TSharedFromThis<FDepositTransaction>
    {
        TOptional<float> PriceValue;
        TOptional<FString> CurrencyValue;
        TOptional<int32> CountValue;
        TOptional<int64> DepositedAtValue;

    public:
        FDepositTransaction();
        FDepositTransaction(
            const FDepositTransaction& From
        );
        virtual ~FDepositTransaction() override = default;

        TSharedPtr<FDepositTransaction> WithPrice(const TOptional<float> Price);
        TSharedPtr<FDepositTransaction> WithCurrency(const TOptional<FString> Currency);
        TSharedPtr<FDepositTransaction> WithCount(const TOptional<int32> Count);
        TSharedPtr<FDepositTransaction> WithDepositedAt(const TOptional<int64> DepositedAt);

        TOptional<float> GetPrice() const;
        FString GetPriceString() const;
        TOptional<FString> GetCurrency() const;
        TOptional<int32> GetCount() const;
        FString GetCountString() const;
        TOptional<int64> GetDepositedAt() const;
        FString GetDepositedAtString() const;


        static TSharedPtr<FDepositTransaction> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDepositTransaction, ESPMode::ThreadSafe> FDepositTransactionPtr;
}