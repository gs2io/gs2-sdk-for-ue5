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
#include "Lottery/Model/Gs2LotteryLotteryModel.h"
#include "Lottery/Model/Gs2LotteryLotteryModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LotteryLotteryModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryLotteryModelGetValueSuccessDelegate, FGs2LotteryLotteryModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryLotteryModelGetValueErrorDelegate, FGs2LotteryLotteryModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LotteryLotteryModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LotteryLotteryModel LotteryModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryLotteryModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryLotteryModelGetValueErrorDelegate OnError;

    UGs2LotteryLotteryModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Lottery::Fetch::GetValueOfLotteryModel", Category="Game Server Services|GS2-Lottery|Namespace|LotteryModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LotteryLotteryModelGetValueAsyncFunction* LotteryModelGetValue(
        UObject* WorldContextObject,
        FGs2LotteryLotteryModel LotteryModel
    );

    virtual void Activate() override;
};