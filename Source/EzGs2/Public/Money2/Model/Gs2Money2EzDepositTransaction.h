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
#include "Money2/Model/DepositTransaction.h"

namespace Gs2::UE5::Money2::Model
{
	class EZGS2_API FEzDepositTransaction final : public TSharedFromThis<FEzDepositTransaction>
	{
        TOptional<float> PriceValue;
        TOptional<FString> CurrencyValue;
        TOptional<int32> CountValue;

	public:
        TSharedPtr<FEzDepositTransaction> WithPrice(const TOptional<float> Price);
        TSharedPtr<FEzDepositTransaction> WithCurrency(const TOptional<FString> Currency);
        TSharedPtr<FEzDepositTransaction> WithCount(const TOptional<int32> Count);

        TOptional<float> GetPrice() const;
        FString GetPriceString() const;

        TOptional<FString> GetCurrency() const;

        TOptional<int32> GetCount() const;
        FString GetCountString() const;

        Gs2::Money2::Model::FDepositTransactionPtr ToModel() const;
        static TSharedPtr<FEzDepositTransaction> FromModel(Gs2::Money2::Model::FDepositTransactionPtr Model);
    };
    typedef TSharedPtr<FEzDepositTransaction> FEzDepositTransactionPtr;
}