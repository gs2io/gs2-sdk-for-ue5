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
#include "Schedule/Model/Gs2ScheduleUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ScheduleListOfTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ScheduleListOfTriggerSuccessDelegate, const TArray<FGs2ScheduleTriggerValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ScheduleListOfTriggerErrorDelegate, const TArray<FGs2ScheduleTriggerValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ScheduleListOfTriggerAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ScheduleOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ScheduleListOfTriggerSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ScheduleListOfTriggerErrorDelegate OnError;

    UGs2ScheduleListOfTriggerAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Schedule::Fetch::ListOfTrigger", Category="Game Server Services|GS2-Schedule|Namespace|User|Trigger|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ScheduleListOfTriggerAsyncFunction* ListOfTrigger(
        UObject* WorldContextObject,
        FGs2ScheduleOwnUser User
    );

    virtual void Activate() override;
};