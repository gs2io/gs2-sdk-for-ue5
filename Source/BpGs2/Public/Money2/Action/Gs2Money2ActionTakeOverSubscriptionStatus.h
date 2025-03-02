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
#include "Money2/Model/Gs2Money2SubscriptionStatus.h"
#include "Money2/Model/Gs2Money2User.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2Money2ActionTakeOverSubscriptionStatus.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2Money2TakeOverSubscriptionStatusSuccessDelegate, FGs2Money2OwnSubscriptionStatus, SubscriptionStatus, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2Money2TakeOverSubscriptionStatusErrorDelegate, FGs2Money2OwnSubscriptionStatus, SubscriptionStatus, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2Money2TakeOverSubscriptionStatusAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2Money2OwnUser User;
    FString Receipt;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2Money2TakeOverSubscriptionStatusSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2Money2TakeOverSubscriptionStatusErrorDelegate OnError;

    UGs2Money2TakeOverSubscriptionStatusAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money2::SubscriptionStatus::Action::TakeOverSubscriptionStatus", Category="Game Server Services|GS2-Money2|Namespace|User|SubscriptionStatus|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2Money2TakeOverSubscriptionStatusAsyncFunction* TakeOverSubscriptionStatus(
        UObject* WorldContextObject,
        FGs2Money2OwnUser User,
        FString Receipt
    );

    virtual void Activate() override;
};