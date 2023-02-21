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
#include "BpGs2/Public/Limit/Model/Gs2LimitUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LimitListOfCounter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitListOfCounterSuccessDelegate, const TArray<FGs2LimitCounterValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitListOfCounterErrorDelegate, const TArray<FGs2LimitCounterValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LimitListOfCounterAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LimitOwnUser User;

public:
    FString LimitName;

    UPROPERTY(BlueprintAssignable)
    FGs2LimitListOfCounterSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2LimitListOfCounterErrorDelegate OnError;

    UGs2LimitListOfCounterAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Limit::Fetch::ListOfCounter", Category="Game Server Services|GS2-Limit|Namespace|User|Counter|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LimitListOfCounterAsyncFunction* ListOfCounter(
        UObject* WorldContextObject,
        FGs2LimitOwnUser User,
        FString LimitName
    );

    virtual void Activate() override;
};