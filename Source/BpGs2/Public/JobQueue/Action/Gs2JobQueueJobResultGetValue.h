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
#include "JobQueue/Model/Gs2JobQueueJobResult.h"
#include "JobQueue/Model/Gs2JobQueueJobResult.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2JobQueueJobResultGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2JobQueueJobResultGetValueSuccessDelegate, FGs2JobQueueJobResultValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2JobQueueJobResultGetValueErrorDelegate, FGs2JobQueueJobResultValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2JobQueueJobResultGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2JobQueueOwnJobResult JobResult;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2JobQueueJobResultGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2JobQueueJobResultGetValueErrorDelegate OnError;

    UGs2JobQueueJobResultGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::JobQueue::Fetch::GetValueOfJobResult", Category="Game Server Services|GS2-JobQueue|Namespace|User|Job|JobResult|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2JobQueueJobResultGetValueAsyncFunction* JobResultGetValue(
        UObject* WorldContextObject,
        FGs2JobQueueOwnJobResult JobResult
    );

    virtual void Activate() override;
};