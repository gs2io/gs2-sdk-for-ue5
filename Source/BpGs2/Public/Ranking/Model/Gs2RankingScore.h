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
#include "Ranking/Domain/Model/Gs2RankingEzScoreGameSessionDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2RankingScore.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingOwnScore
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RankingScoreValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString CategoryName = "";
    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString UniqueId = "";
    UPROPERTY(BlueprintReadOnly)
    FString ScorerUserId = "";
    UPROPERTY(BlueprintReadOnly)
    int64 Score = 0;
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
};

inline FGs2RankingScoreValue EzScoreToFGs2RankingScoreValue(
    const Gs2::UE5::Ranking::Model::FEzScorePtr Model
)
{
    FGs2RankingScoreValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingScoreFunctionLibrary::EzScoreToFGs2RankingScoreValue] Model parameter specification is missing."))
        return Value;
    }
    Value.CategoryName = Model->GetCategoryName() ? *Model->GetCategoryName() : "";
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.UniqueId = Model->GetUniqueId() ? *Model->GetUniqueId() : "";
    Value.ScorerUserId = Model->GetScorerUserId() ? *Model->GetScorerUserId() : "";
    Value.Score = Model->GetScore() ? *Model->GetScore() : 0;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    return Value;
}

inline Gs2::UE5::Ranking::Model::FEzScorePtr FGs2RankingScoreValueToEzScore(
    const FGs2RankingScoreValue Model
)
{
    return MakeShared<Gs2::UE5::Ranking::Model::FEzScore>()
        ->WithCategoryName(Model.CategoryName)
        ->WithUserId(Model.UserId)
        ->WithUniqueId(Model.UniqueId)
        ->WithScorerUserId(Model.ScorerUserId)
        ->WithScore(Model.Score)
        ->WithMetadata(Model.Metadata);
}

UCLASS()
class BPGS2_API UGs2RankingScoreFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};