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
#include "Ranking/Model/Gs2RankingScore.h"
#include "Ranking/Model/Gs2RankingRankingCategory.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RankingActionPutScore.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingPutScoreSuccessDelegate, FGs2RankingOwnScore, Score, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingPutScoreErrorDelegate, FGs2RankingOwnScore, Score, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RankingPutScoreAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RankingOwnRankingCategory RankingCategory;
    int64 Score;
    FString Metadata;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingPutScoreSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingPutScoreErrorDelegate OnError;

    UGs2RankingPutScoreAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Ranking::Action::PutScore", Category="Game Server Services|GS2-Ranking|Namespace|User|RankingCategory|Ranking|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RankingPutScoreAsyncFunction* PutScore(
        UObject* WorldContextObject,
        FGs2RankingOwnRankingCategory RankingCategory,
        int64 Score,
        FString Metadata
    );

    virtual void Activate() override;
};