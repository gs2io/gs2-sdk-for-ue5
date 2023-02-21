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
#include "BpGs2/Public/Lottery/Model/Gs2LotteryUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LotteryListOfProbability.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryListOfProbabilitySuccessDelegate, const TArray<FGs2LotteryProbability>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryListOfProbabilityErrorDelegate, const TArray<FGs2LotteryProbability>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LotteryListOfProbabilityAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LotteryOwnUser User;

public:
    FString LotteryName;

    UPROPERTY(BlueprintAssignable)
    FGs2LotteryListOfProbabilitySuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2LotteryListOfProbabilityErrorDelegate OnError;

    UGs2LotteryListOfProbabilityAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Lottery::Fetch::ListOfProbability", Category="Game Server Services|GS2-Lottery|Namespace|User|Probability|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LotteryListOfProbabilityAsyncFunction* ListOfProbability(
        UObject* WorldContextObject,
        FGs2LotteryOwnUser User,
        FString LotteryName
    );

    virtual void Activate() override;
};