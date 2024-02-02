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
#include "Ranking/Model/Gs2RankingSubscribeUser.h"
#include "Ranking/Model/Gs2RankingRankingCategory.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RankingActionSubscribe.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingSubscribeSuccessDelegate, FGs2RankingOwnSubscribeUser, SubscribeUser, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingSubscribeErrorDelegate, FGs2RankingOwnSubscribeUser, SubscribeUser, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RankingSubscribeAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RankingOwnRankingCategory RankingCategory;
    FString TargetUserId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingSubscribeSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingSubscribeErrorDelegate OnError;

    UGs2RankingSubscribeAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::Subscribe::Action::Subscribe", Category="Game Server Services|GS2-Ranking|Namespace|User|RankingCategory|Subscribe|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RankingSubscribeAsyncFunction* Subscribe(
        UObject* WorldContextObject,
        FGs2RankingOwnRankingCategory RankingCategory,
        FString TargetUserId
    );

    virtual void Activate() override;
};