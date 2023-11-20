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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Ranking/Model/Gs2RankingUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RankingListOfRanking.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingListOfRankingSuccessDelegate, const TArray<FGs2RankingRankingValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingListOfRankingErrorDelegate, const TArray<FGs2RankingRankingValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RankingListOfRankingAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RankingOwnUser User;
    FString CategoryName;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingListOfRankingSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingListOfRankingErrorDelegate OnError;

    UGs2RankingListOfRankingAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Fetch::ListOfRanking", Category="Game Server Services|GS2-Ranking|Namespace|User|Ranking|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RankingListOfRankingAsyncFunction* ListOfRanking(
        UObject* WorldContextObject,
        FGs2RankingOwnUser User,
        FString CategoryName
    );

    virtual void Activate() override;
};