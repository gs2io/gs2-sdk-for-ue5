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
#include "Limit/Model/Gs2LimitCounter.h"
#include "Limit/Model/Gs2LimitCounter.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LimitActionCountUp.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitCountUpSuccessDelegate, FGs2LimitOwnCounter, Counter, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitCountUpErrorDelegate, FGs2LimitOwnCounter, Counter, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LimitCountUpAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LimitOwnCounter Counter;
    int32 CountUpValue;
    int32 MaxValue;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LimitCountUpSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LimitCountUpErrorDelegate OnError;

    UGs2LimitCountUpAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Limit::Counter::Action::CountUp", Category="Game Server Services|GS2-Limit|Namespace|User|Counter|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LimitCountUpAsyncFunction* CountUp(
        UObject* WorldContextObject,
        FGs2LimitOwnCounter Counter,
        int32 CountUpValue,
        int32 MaxValue
    );

    virtual void Activate() override;
};