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
#include "BpGs2/Public/Mission/Model/Gs2MissionCounter.h"
#include "BpGs2/Public/Mission/Model/Gs2MissionCounter.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MissionCounterGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionCounterGetValueSuccessDelegate, FGs2MissionCounterValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionCounterGetValueErrorDelegate, FGs2MissionCounterValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MissionCounterGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MissionOwnCounter Counter;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionCounterGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionCounterGetValueErrorDelegate OnError;

    UGs2MissionCounterGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::Fetch::GetValueOfCounter", Category="Game Server Services|GS2-Mission|Namespace|User|Counter|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MissionCounterGetValueAsyncFunction* CounterGetValue(
        UObject* WorldContextObject,
        FGs2MissionOwnCounter Counter
    );

    virtual void Activate() override;
};