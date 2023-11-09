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
#include "Experience/Domain/Model/Gs2ExperienceEzExperienceModelDomain.h"
#include "Experience/Model/Gs2ExperienceThreshold.h"
#include "Experience/Model/Gs2ExperienceAcquireActionRate.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ExperienceExperienceModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExperienceExperienceModel
{
    GENERATED_BODY()

    Gs2::UE5::Experience::Domain::Model::FEzExperienceModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ExperienceExperienceModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 DefaultExperience = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 DefaultRankCap = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 MaxRankCap = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2ExperienceThreshold RankThreshold = FGs2ExperienceThreshold();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2ExperienceAcquireActionRate> AcquireActionRates = TArray<FGs2ExperienceAcquireActionRate>();
};

inline FGs2ExperienceExperienceModelValue EzExperienceModelToFGs2ExperienceExperienceModelValue(
    const Gs2::UE5::Experience::Model::FEzExperienceModelPtr Model
)
{
    FGs2ExperienceExperienceModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExperienceExperienceModelFunctionLibrary::EzExperienceModelToFGs2ExperienceExperienceModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.DefaultExperience = Model->GetDefaultExperience() ? *Model->GetDefaultExperience() : 0;
    Value.DefaultRankCap = Model->GetDefaultRankCap() ? *Model->GetDefaultRankCap() : 0;
    Value.MaxRankCap = Model->GetMaxRankCap() ? *Model->GetMaxRankCap() : 0;
    Value.RankThreshold = Model->GetRankThreshold() ? EzThresholdToFGs2ExperienceThreshold(Model->GetRankThreshold()) : FGs2ExperienceThreshold();
    Value.AcquireActionRates = Model->GetAcquireActionRates() ? [&]
    {
        TArray<FGs2ExperienceAcquireActionRate> r;
        for (auto v : *Model->GetAcquireActionRates())
        {
            r.Add(EzAcquireActionRateToFGs2ExperienceAcquireActionRate(v));
        }
        return r;
    }() : TArray<FGs2ExperienceAcquireActionRate>();
    return Value;
}

inline Gs2::UE5::Experience::Model::FEzExperienceModelPtr FGs2ExperienceExperienceModelValueToEzExperienceModel(
    const FGs2ExperienceExperienceModelValue Model
)
{
    return MakeShared<Gs2::UE5::Experience::Model::FEzExperienceModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithDefaultExperience(Model.DefaultExperience)
        ->WithDefaultRankCap(Model.DefaultRankCap)
        ->WithMaxRankCap(Model.MaxRankCap)
        ->WithRankThreshold(FGs2ExperienceThresholdToEzThreshold(Model.RankThreshold))
        ->WithAcquireActionRates([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Experience::Model::FEzAcquireActionRatePtr>>();
            for (auto v : Model.AcquireActionRates) {
                r->Add(FGs2ExperienceAcquireActionRateToEzAcquireActionRate(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2ExperienceExperienceModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};