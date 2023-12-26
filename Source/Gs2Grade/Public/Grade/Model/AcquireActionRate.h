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

namespace Gs2::Grade::Model
{
    class GS2GRADE_API FAcquireActionRate final : public Gs2Object, public TSharedFromThis<FAcquireActionRate>
    {
        TOptional<FString> NameValue;
        TOptional<FString> ModeValue;
        TSharedPtr<TArray<double>> RatesValue;
        TSharedPtr<TArray<FString>> BigRatesValue;

    public:
        FAcquireActionRate();
        FAcquireActionRate(
            const FAcquireActionRate& From
        );
        virtual ~FAcquireActionRate() override = default;

        TSharedPtr<FAcquireActionRate> WithName(const TOptional<FString> Name);
        TSharedPtr<FAcquireActionRate> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FAcquireActionRate> WithRates(const TSharedPtr<TArray<double>> Rates);
        TSharedPtr<FAcquireActionRate> WithBigRates(const TSharedPtr<TArray<FString>> BigRates);

        TOptional<FString> GetName() const;
        TOptional<FString> GetMode() const;
        TSharedPtr<TArray<double>> GetRates() const;
        TSharedPtr<TArray<FString>> GetBigRates() const;


        static TSharedPtr<FAcquireActionRate> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAcquireActionRate, ESPMode::ThreadSafe> FAcquireActionRatePtr;
}