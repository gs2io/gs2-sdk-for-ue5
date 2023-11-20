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
#include "JobQueue/Model/Gs2JobQueueJob.h"
#include "JobQueue/Model/Gs2JobQueueUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2JobQueueActionRun.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2JobQueueRunSuccessDelegate, FGs2JobQueueOwnJob, Job, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2JobQueueRunErrorDelegate, FGs2JobQueueOwnJob, Job, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2JobQueueRunAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2JobQueueOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2JobQueueRunSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2JobQueueRunErrorDelegate OnError;

    UGs2JobQueueRunAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::JobQueue::Job::Action::Run", Category="Game Server Services|GS2-JobQueue|Namespace|User|Job|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2JobQueueRunAsyncFunction* Run(
        UObject* WorldContextObject,
        FGs2JobQueueOwnUser User
    );

    virtual void Activate() override;
};