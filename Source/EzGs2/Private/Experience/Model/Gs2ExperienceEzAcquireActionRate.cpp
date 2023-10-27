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

#include "EzGs2/Public/Experience/Model/Gs2ExperienceEzAcquireActionRate.h"

namespace Gs2::UE5::Experience::Model
{

    TSharedPtr<FEzAcquireActionRate> FEzAcquireActionRate::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcquireActionRate> FEzAcquireActionRate::WithMode(
        const TOptional<FString> Mode
    )
    {
        this->ModeValue = Mode;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcquireActionRate> FEzAcquireActionRate::WithRates(
        const TSharedPtr<TArray<double>> Rates
    )
    {
        this->RatesValue = Rates;
        return SharedThis(this);
    }

    TSharedPtr<FEzAcquireActionRate> FEzAcquireActionRate::WithBigRates(
        const TSharedPtr<TArray<FString>> BigRates
    )
    {
        this->BigRatesValue = BigRates;
        return SharedThis(this);
    }
    TOptional<FString> FEzAcquireActionRate::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzAcquireActionRate::GetMode() const
    {
        return ModeValue;
    }
    TSharedPtr<TArray<double>> FEzAcquireActionRate::GetRates() const
    {
        return RatesValue;
    }
    TSharedPtr<TArray<FString>> FEzAcquireActionRate::GetBigRates() const
    {
        return BigRatesValue;
    }

    Gs2::Experience::Model::FAcquireActionRatePtr FEzAcquireActionRate::ToModel() const
    {
        return MakeShared<Gs2::Experience::Model::FAcquireActionRate>()
            ->WithName(NameValue)
            ->WithMode(ModeValue)
            ->WithRates(RatesValue)
            ->WithBigRates(BigRatesValue);
    }

    TSharedPtr<FEzAcquireActionRate> FEzAcquireActionRate::FromModel(const Gs2::Experience::Model::FAcquireActionRatePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzAcquireActionRate>()
            ->WithName(Model->GetName())
            ->WithMode(Model->GetMode())
            ->WithRates(Model->GetRates())
            ->WithBigRates(Model->GetBigRates());
    }
}