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
#include "SeasonRating/Domain/Model/Gs2SeasonRatingEzSeasonModelDomain.h"
#include "SeasonRating/Model/Gs2SeasonRatingTierModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2SeasonRatingSeasonModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2SeasonRatingSeasonModel
{
    GENERATED_BODY()

    Gs2::UE5::SeasonRating::Domain::Model::FEzSeasonModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2SeasonRatingSeasonModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2SeasonRatingTierModel> Tiers = TArray<FGs2SeasonRatingTierModel>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ExperienceModelId = "";
};

inline FGs2SeasonRatingSeasonModelValue EzSeasonModelToFGs2SeasonRatingSeasonModelValue(
    const Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr Model
)
{
    FGs2SeasonRatingSeasonModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SeasonRatingSeasonModelFunctionLibrary::EzSeasonModelToFGs2SeasonRatingSeasonModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.Tiers = Model->GetTiers() ? [&]
    {
        TArray<FGs2SeasonRatingTierModel> r;
        for (auto v : *Model->GetTiers())
        {
            r.Add(EzTierModelToFGs2SeasonRatingTierModel(v));
        }
        return r;
    }() : TArray<FGs2SeasonRatingTierModel>();
    Value.ExperienceModelId = Model->GetExperienceModelId() ? *Model->GetExperienceModelId() : "";
    return Value;
}

inline Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr FGs2SeasonRatingSeasonModelValueToEzSeasonModel(
    const FGs2SeasonRatingSeasonModelValue Model
)
{
    return MakeShared<Gs2::UE5::SeasonRating::Model::FEzSeasonModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTiers([&]{
            auto r = MakeShared<TArray<Gs2::UE5::SeasonRating::Model::FEzTierModelPtr>>();
            for (auto v : Model.Tiers) {
                r->Add(FGs2SeasonRatingTierModelToEzTierModel(v));
            }
            return r;
        }())
        ->WithExperienceModelId(Model.ExperienceModelId);
}

UCLASS()
class BPGS2_API UGs2SeasonRatingSeasonModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};