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
#include "Ranking/Model/Gs2RankingRankingCategory.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RankingListOfSubscribeUser.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingListOfSubscribeUserSuccessDelegate, const TArray<FGs2RankingSubscribeUserValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingListOfSubscribeUserErrorDelegate, const TArray<FGs2RankingSubscribeUserValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RankingListOfSubscribeUserAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RankingOwnRankingCategory RankingCategory;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingListOfSubscribeUserSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingListOfSubscribeUserErrorDelegate OnError;

    UGs2RankingListOfSubscribeUserAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Fetch::ListOfSubscribeUser", Category="Game Server Services|GS2-Ranking|Namespace|User|RankingCategory|SubscribeUser|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RankingListOfSubscribeUserAsyncFunction* ListOfSubscribeUser(
        UObject* WorldContextObject,
        FGs2RankingOwnRankingCategory RankingCategory
    );

    virtual void Activate() override;
};