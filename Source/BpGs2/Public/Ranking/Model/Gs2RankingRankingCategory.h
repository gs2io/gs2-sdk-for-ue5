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
#include "Ranking/Domain/Model/Gs2RankingEzRankingCategoryGameSessionDomain.h"
#include "Ranking/Domain/Model/Gs2RankingEzRankingCategoryDomain.h"
#include "Core/BpGs2Constant.h"
#include "Gs2RankingRankingCategory.generated.h"

USTRUCT(BlueprintType)
struct FGs2RankingOwnRankingCategory
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzRankingCategoryGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RankingRankingCategory
{
    GENERATED_BODY()

    Gs2::UE5::Ranking::Domain::Model::FEzRankingCategoryDomainPtr Value = nullptr;
};

UCLASS()
class BPGS2_API UGs2RankingRankingCategoryFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::OwnSubscribeUser", Category="Game Server Services|GS2-Ranking|Namespace|User|RankingCategory|SubscribeUser", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="SubscribeUser") FGs2RankingOwnSubscribeUser OwnSubscribeUser(
        FGs2RankingOwnRankingCategory RankingCategory,
        FString TargetUserId
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Ranking", Category="Game Server Services|GS2-Ranking|Namespace|User|RankingCategory|Ranking", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Ranking") FGs2RankingRanking Ranking(
        FGs2RankingRankingCategory RankingCategory,
        FString ScorerUserId,
        int64 Index
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::OwnRanking", Category="Game Server Services|GS2-Ranking|Namespace|User|RankingCategory|Ranking", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Ranking") FGs2RankingOwnRanking OwnRanking(
        FGs2RankingOwnRankingCategory RankingCategory,
        FString ScorerUserId,
        int64 Index
    );
};