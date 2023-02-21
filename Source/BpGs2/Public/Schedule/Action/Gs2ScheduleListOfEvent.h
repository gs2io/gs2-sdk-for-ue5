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
#include "BpGs2/Public/Schedule/Model/Gs2ScheduleUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ScheduleListOfEvent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ScheduleListOfEventSuccessDelegate, const TArray<FGs2ScheduleEventValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ScheduleListOfEventErrorDelegate, const TArray<FGs2ScheduleEventValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ScheduleListOfEventAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ScheduleOwnUser User;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2ScheduleListOfEventSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2ScheduleListOfEventErrorDelegate OnError;

    UGs2ScheduleListOfEventAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Schedule::Fetch::ListOfEvent", Category="Game Server Services|GS2-Schedule|Namespace|User|Event|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ScheduleListOfEventAsyncFunction* ListOfEvent(
        UObject* WorldContextObject,
        FGs2ScheduleOwnUser User
    );

    virtual void Activate() override;
};