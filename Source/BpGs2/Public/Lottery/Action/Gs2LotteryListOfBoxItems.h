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
#include "Gs2LotteryListOfBoxItems.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryListOfBoxItemsSuccessDelegate, const TArray<FGs2LotteryBoxItemsValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LotteryListOfBoxItemsErrorDelegate, const TArray<FGs2LotteryBoxItemsValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LotteryListOfBoxItemsAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LotteryOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryListOfBoxItemsSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LotteryListOfBoxItemsErrorDelegate OnError;

    UGs2LotteryListOfBoxItemsAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Lottery::Fetch::ListOfBoxItems", Category="Game Server Services|GS2-Lottery|Namespace|User|BoxItems|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LotteryListOfBoxItemsAsyncFunction* ListOfBoxItems(
        UObject* WorldContextObject,
        FGs2LotteryOwnUser User
    );

    virtual void Activate() override;
};