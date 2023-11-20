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
#include "SkillTree/Model/Gs2SkillTreeStatus.h"
#include "SkillTree/Model/Gs2SkillTreeStatus.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2SkillTreeStatusGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SkillTreeStatusGetValueSuccessDelegate, FGs2SkillTreeStatusValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SkillTreeStatusGetValueErrorDelegate, FGs2SkillTreeStatusValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2SkillTreeStatusGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2SkillTreeOwnStatus Status;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2SkillTreeStatusGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2SkillTreeStatusGetValueErrorDelegate OnError;

    UGs2SkillTreeStatusGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::SkillTree::Fetch::GetValueOfStatus", Category="Game Server Services|GS2-SkillTree|Namespace|User|Status|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2SkillTreeStatusGetValueAsyncFunction* StatusGetValue(
        UObject* WorldContextObject,
        FGs2SkillTreeOwnStatus Status
    );

    virtual void Activate() override;
};