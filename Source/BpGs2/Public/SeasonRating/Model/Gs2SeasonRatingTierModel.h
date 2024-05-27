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

#include "SeasonRating/Model/Gs2SeasonRatingEzTierModel.h"
#include "Gs2SeasonRatingTierModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2SeasonRatingTierModel
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 RaiseRankBonus = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 MinimumChangePoint = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 MaximumChangePoint = 0;
};

inline FGs2SeasonRatingTierModel EzTierModelToFGs2SeasonRatingTierModel(
    const Gs2::UE5::SeasonRating::Model::FEzTierModelPtr Model
)
{
    FGs2SeasonRatingTierModel Value;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.RaiseRankBonus = Model->GetRaiseRankBonus() ? *Model->GetRaiseRankBonus() : 0;
    Value.MinimumChangePoint = Model->GetMinimumChangePoint() ? *Model->GetMinimumChangePoint() : 0;
    Value.MaximumChangePoint = Model->GetMaximumChangePoint() ? *Model->GetMaximumChangePoint() : 0;
    return Value;
}

inline Gs2::UE5::SeasonRating::Model::FEzTierModelPtr FGs2SeasonRatingTierModelToEzTierModel(
    const FGs2SeasonRatingTierModel Model
)
{
    return MakeShared<Gs2::UE5::SeasonRating::Model::FEzTierModel>()
        ->WithMetadata(Model.Metadata)
        ->WithRaiseRankBonus(Model.RaiseRankBonus)
        ->WithMinimumChangePoint(Model.MinimumChangePoint)
        ->WithMaximumChangePoint(Model.MaximumChangePoint);
}