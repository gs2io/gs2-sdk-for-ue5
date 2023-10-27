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

#include "Experience/Model/Gs2ExperienceEzAcquireActionRate.h"
#include "Gs2ExperienceAcquireActionRate.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExperienceAcquireActionRate
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    FString Mode = "";
    UPROPERTY(BlueprintReadWrite)
    TArray<double> Rates = TArray<double>();
    UPROPERTY(BlueprintReadWrite)
    TArray<FString> BigRates = TArray<FString>();
};

inline FGs2ExperienceAcquireActionRate EzAcquireActionRateToFGs2ExperienceAcquireActionRate(
    const Gs2::UE5::Experience::Model::FEzAcquireActionRatePtr Model
)
{
    FGs2ExperienceAcquireActionRate Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Mode = Model->GetMode() ? *Model->GetMode() : "";
    Value.Rates = Model->GetRates() ? [&]
    {
        TArray<double> r;
        for (auto v : *Model->GetRates())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<double>();
    Value.BigRates = Model->GetBigRates() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetBigRates())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Experience::Model::FEzAcquireActionRatePtr FGs2ExperienceAcquireActionRateToEzAcquireActionRate(
    const FGs2ExperienceAcquireActionRate Model
)
{
    return MakeShared<Gs2::UE5::Experience::Model::FEzAcquireActionRate>()
        ->WithName(Model.Name)
        ->WithMode(Model.Mode)
        ->WithRates([&]{
            auto r = MakeShared<TArray<double>>();
            for (auto v : Model.Rates) {
                r->Add(v);
            }
            return r;
        }())
        ->WithBigRates([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.BigRates) {
                r->Add(v);
            }
            return r;
        }());
}