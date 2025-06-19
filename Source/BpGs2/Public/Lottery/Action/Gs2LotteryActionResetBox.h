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
#include "Lottery/Model/Gs2LotteryBoxItems.h"
#include "Lottery/Model/Gs2LotteryBoxItems.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LotteryActionResetBox.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryResetBoxSuccessDelegate, FGs2LotteryOwnBoxItems, BoxItems, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryResetBoxErrorDelegate, FGs2LotteryOwnBoxItems, BoxItems, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LotteryResetBoxAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LotteryOwnBoxItems BoxItems;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryResetBoxSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryResetBoxErrorDelegate OnError;

    UGs2LotteryResetBoxAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Lottery::BoxItems::Action::ResetBox", Category="Game Server Services|GS2-Lottery|Namespace|User|BoxItems|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LotteryResetBoxAsyncFunction* ResetBox(
        UObject* WorldContextObject,
        FGs2LotteryOwnBoxItems BoxItems
    );

    virtual void Activate() override;
};