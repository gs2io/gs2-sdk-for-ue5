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

#include "SeasonRating/Model/Gs2SeasonRatingEzGameResult.h"
#include "Gs2SeasonRatingGameResult.generated.h"

USTRUCT(BlueprintType)
struct FGs2SeasonRatingGameResult
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    int32 Rank = 0;
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString UserId = "";
};

inline FGs2SeasonRatingGameResult EzGameResultToFGs2SeasonRatingGameResult(
    const Gs2::UE5::SeasonRating::Model::FEzGameResultPtr Model
)
{
    FGs2SeasonRatingGameResult Value;
    Value.Rank = Model->GetRank() ? *Model->GetRank() : 0;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    return Value;
}

inline Gs2::UE5::SeasonRating::Model::FEzGameResultPtr FGs2SeasonRatingGameResultToEzGameResult(
    const FGs2SeasonRatingGameResult Model
)
{
    return MakeShared<Gs2::UE5::SeasonRating::Model::FEzGameResult>()
        ->WithRank(Model.Rank)
        ->WithUserId(Model.UserId);
}