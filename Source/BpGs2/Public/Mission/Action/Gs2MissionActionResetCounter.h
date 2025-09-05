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
#include "Mission/Model/Gs2MissionCounter.h"
#include "Mission/Model/Gs2MissionScopedValue.h"
#include "Mission/Model/Gs2MissionCounter.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MissionActionResetCounter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionResetCounterSuccessDelegate, FGs2MissionOwnCounter, Counter, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionResetCounterErrorDelegate, FGs2MissionOwnCounter, Counter, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MissionResetCounterAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MissionOwnCounter Counter;
    TArray<FGs2MissionScopedValue> Scopes;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionResetCounterSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionResetCounterErrorDelegate OnError;

    UGs2MissionResetCounterAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::Counter::Action::ResetCounter", Category="Game Server Services|GS2-Mission|Namespace|User|Counter|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MissionResetCounterAsyncFunction* ResetCounter(
        UObject* WorldContextObject,
        FGs2MissionOwnCounter Counter,
        TArray<FGs2MissionScopedValue> Scopes
    );

    virtual void Activate() override;
};