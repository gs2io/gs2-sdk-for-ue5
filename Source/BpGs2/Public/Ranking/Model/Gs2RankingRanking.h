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
#include "Ranking/Domain/Model/Gs2RankingEzRankingGameSessionDomain.h"
#include "Ranking/Domain/Model/Gs2RankingEzRankingDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2RankingRanking.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingOwnRanking
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzRankingGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RankingRanking
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzRankingDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RankingRankingValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Rank = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Index = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 Score = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 CreatedAt = 0;
};

inline FGs2RankingRankingValue EzRankingToFGs2RankingRankingValue(
    const Gs2::UE5::Ranking::Model::FEzRankingPtr Model
)
{
    FGs2RankingRankingValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2RankingRankingFunctionLibrary::EzRankingToFGs2RankingRankingValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Rank = Model->GetRank() ? *Model->GetRank() : 0;
    Value.Index = Model->GetIndex() ? *Model->GetIndex() : 0;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.Score = Model->GetScore() ? *Model->GetScore() : 0;
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.CreatedAt = Model->GetCreatedAt() ? *Model->GetCreatedAt() : 0;
    return Value;
}

inline Gs2::UE5::Ranking::Model::FEzRankingPtr FGs2RankingRankingValueToEzRanking(
    const FGs2RankingRankingValue Model
)
{
    return MakeShared<Gs2::UE5::Ranking::Model::FEzRanking>()
        ->WithRank(Model.Rank)
        ->WithIndex(Model.Index)
        ->WithUserId(Model.UserId)
        ->WithScore(Model.Score)
        ->WithMetadata(Model.Metadata)
        ->WithCreatedAt(Model.CreatedAt);
}

UCLASS()
class BPGS2_API UGs2RankingRankingFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};