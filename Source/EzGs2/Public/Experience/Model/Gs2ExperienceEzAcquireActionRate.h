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
#include "Experience/Model/AcquireActionRate.h"

namespace Gs2::UE5::Experience::Model
{
	class EZGS2_API FEzAcquireActionRate final : public TSharedFromThis<FEzAcquireActionRate>
	{
        TOptional<FString> NameValue;
        TOptional<FString> ModeValue;
        TSharedPtr<TArray<double>> RatesValue;
        TSharedPtr<TArray<FString>> BigRatesValue;

	public:
        TSharedPtr<FEzAcquireActionRate> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzAcquireActionRate> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FEzAcquireActionRate> WithRates(const TSharedPtr<TArray<double>> Rates);
        TSharedPtr<FEzAcquireActionRate> WithBigRates(const TSharedPtr<TArray<FString>> BigRates);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMode() const;

        TSharedPtr<TArray<double>> GetRates() const;

        TSharedPtr<TArray<FString>> GetBigRates() const;

        Gs2::Experience::Model::FAcquireActionRatePtr ToModel() const;
        static TSharedPtr<FEzAcquireActionRate> FromModel(Gs2::Experience::Model::FAcquireActionRatePtr Model);
    };
    typedef TSharedPtr<FEzAcquireActionRate> FEzAcquireActionRatePtr;
}