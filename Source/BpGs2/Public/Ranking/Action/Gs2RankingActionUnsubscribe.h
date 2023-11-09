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
#include "BpGs2/Public/Ranking/Model/Gs2RankingSubscribeUser.h"
#include "BpGs2/Public/Ranking/Model/Gs2RankingSubscribeUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RankingActionUnsubscribe.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingUnsubscribeSuccessDelegate, FGs2RankingOwnSubscribeUser, SubscribeUser, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RankingUnsubscribeErrorDelegate, FGs2RankingOwnSubscribeUser, SubscribeUser, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RankingUnsubscribeAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RankingOwnSubscribeUser SubscribeUser;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingUnsubscribeSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RankingUnsubscribeErrorDelegate OnError;

    UGs2RankingUnsubscribeAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Ranking::SubscribeUser::Action::Unsubscribe", Category="Game Server Services|GS2-Ranking|Namespace|User|SubscribeUser|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RankingUnsubscribeAsyncFunction* Unsubscribe(
        UObject* WorldContextObject,
        FGs2RankingOwnSubscribeUser SubscribeUser
    );

    virtual void Activate() override;
};