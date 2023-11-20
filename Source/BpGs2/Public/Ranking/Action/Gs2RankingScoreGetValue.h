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
#include "Ranking/Model/Gs2RankingScore.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RankingScoreGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingScoreGetValueSuccessDelegate, FGs2RankingScoreValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingScoreGetValueErrorDelegate, FGs2RankingScoreValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RankingScoreGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RankingOwnScore Score;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingScoreGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingScoreGetValueErrorDelegate OnError;

    UGs2RankingScoreGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Fetch::GetValueOfScore", Category="Game Server Services|GS2-Ranking|Namespace|User|Score|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RankingScoreGetValueAsyncFunction* ScoreGetValue(
        UObject* WorldContextObject,
        FGs2RankingOwnScore Score
    );

    virtual void Activate() override;
};