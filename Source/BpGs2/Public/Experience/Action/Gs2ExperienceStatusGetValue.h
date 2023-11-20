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
#include "Experience/Model/Gs2ExperienceStatus.h"
#include "Experience/Model/Gs2ExperienceStatus.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExperienceStatusGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceStatusGetValueSuccessDelegate, FGs2ExperienceStatusValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceStatusGetValueErrorDelegate, FGs2ExperienceStatusValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExperienceStatusGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ExperienceOwnStatus Status;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceStatusGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceStatusGetValueErrorDelegate OnError;

    UGs2ExperienceStatusGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Experience::Fetch::GetValueOfStatus", Category="Game Server Services|GS2-Experience|Namespace|User|Status|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExperienceStatusGetValueAsyncFunction* StatusGetValue(
        UObject* WorldContextObject,
        FGs2ExperienceOwnStatus Status
    );

    virtual void Activate() override;
};