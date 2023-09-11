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
#include "BpGs2/Public/SkillTree/Model/Gs2SkillTreeStatus.h"
#include "BpGs2/Public/SkillTree/Model/Gs2SkillTreeStatus.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2SkillTreeActionReset.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SkillTreeResetSuccessDelegate, FGs2SkillTreeOwnStatus, Status, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2SkillTreeResetErrorDelegate, FGs2SkillTreeOwnStatus, Status, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2SkillTreeResetAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2SkillTreeOwnStatus Status;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2SkillTreeResetSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2SkillTreeResetErrorDelegate OnError;

    UGs2SkillTreeResetAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::SkillTree::Status::Action::Reset", Category="Game Server Services|GS2-SkillTree|Namespace|User|Status|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2SkillTreeResetAsyncFunction* Reset(
        UObject* WorldContextObject,
        FGs2SkillTreeOwnStatus Status
    );

    virtual void Activate() override;
};