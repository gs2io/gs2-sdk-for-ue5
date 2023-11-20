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
#include "LoginReward/Model/Gs2LoginRewardUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LoginRewardListOfReceiveStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LoginRewardListOfReceiveStatusSuccessDelegate, const TArray<FGs2LoginRewardReceiveStatusValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LoginRewardListOfReceiveStatusErrorDelegate, const TArray<FGs2LoginRewardReceiveStatusValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LoginRewardListOfReceiveStatusAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LoginRewardOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LoginRewardListOfReceiveStatusSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LoginRewardListOfReceiveStatusErrorDelegate OnError;

    UGs2LoginRewardListOfReceiveStatusAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::LoginReward::Fetch::ListOfReceiveStatus", Category="Game Server Services|GS2-LoginReward|Namespace|User|ReceiveStatus|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LoginRewardListOfReceiveStatusAsyncFunction* ListOfReceiveStatus(
        UObject* WorldContextObject,
        FGs2LoginRewardOwnUser User
    );

    virtual void Activate() override;
};