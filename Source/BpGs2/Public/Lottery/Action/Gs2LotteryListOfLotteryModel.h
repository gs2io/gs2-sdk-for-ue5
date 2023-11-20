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
#include "Lottery/Model/Gs2LotteryNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LotteryListOfLotteryModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryListOfLotteryModelSuccessDelegate, const TArray<FGs2LotteryLotteryModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryListOfLotteryModelErrorDelegate, const TArray<FGs2LotteryLotteryModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LotteryListOfLotteryModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LotteryNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryListOfLotteryModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryListOfLotteryModelErrorDelegate OnError;

    UGs2LotteryListOfLotteryModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Lottery::Fetch::ListOfLotteryModel", Category="Game Server Services|GS2-Lottery|Namespace|LotteryModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LotteryListOfLotteryModelAsyncFunction* ListOfLotteryModel(
        UObject* WorldContextObject,
        FGs2LotteryNamespace Namespace
    );

    virtual void Activate() override;
};