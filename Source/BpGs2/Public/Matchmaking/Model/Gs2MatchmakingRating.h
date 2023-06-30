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
#include "Matchmaking/Domain/Model/Gs2MatchmakingEzRatingGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2MatchmakingRating.generated.h"

USTRUCT(BlueprintType)
struct FGs2MatchmakingOwnRating
{
    GENERATED_BODY()

    Gs2::UE5::Matchmaking::Domain::Model::FEzRatingGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2MatchmakingRatingValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString RatingId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    float RateValue = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 CreatedAt = 0;
    UPROPERTY(BlueprintReadOnly)
    int64 UpdatedAt = 0;
};

inline FGs2MatchmakingRatingValue EzRatingToFGs2MatchmakingRatingValue(
    const Gs2::UE5::Matchmaking::Model::FEzRatingPtr Model
)
{
    FGs2MatchmakingRatingValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2MatchmakingRatingFunctionLibrary::EzRatingToFGs2MatchmakingRatingValue] Model parameter specification is missing."))
        return Value;
    }
    Value.RatingId = Model->GetRatingId() ? *Model->GetRatingId() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.RateValue = Model->GetRateValue() ? *Model->GetRateValue() : 0;
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    Value.UpdatedAt = Model->GetUpdatedAt() ? *Model->GetUpdatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Matchmaking::Model::FEzRatingPtr FGs2MatchmakingRatingValueToEzRating(
    const FGs2MatchmakingRatingValue Model
)
{
    return MakeShared<Gs2::UE5::Matchmaking::Model::FEzRating>()
        ->WithRatingId(Model.RatingId)
        ->WithName(Model.Name)
        ->WithUserId(Model.UserId)
        ->WithRateValue(Model.RateValue)
        ->WithCreatedAt(Model.CreatedAt)
        ->WithUpdatedAt(Model.UpdatedAt);
}

UCLASS()
class BPGS2_API UGs2MatchmakingRatingFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};