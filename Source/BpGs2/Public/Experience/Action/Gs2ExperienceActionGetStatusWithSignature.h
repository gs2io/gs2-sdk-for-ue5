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
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExperienceActionGetStatusWithSignature.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceGetStatusWithSignatureSuccessDelegate, FGs2ExperienceOwnStatus, Status, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceGetStatusWithSignatureErrorDelegate, FGs2ExperienceOwnStatus, Status, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExperienceGetStatusWithSignatureAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ExperienceOwnStatus Status;
    FString KeyId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceGetStatusWithSignatureSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceGetStatusWithSignatureErrorDelegate OnError;

    UGs2ExperienceGetStatusWithSignatureAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Experience::Status::Action::GetStatusWithSignature", Category="Game Server Services|GS2-Experience|Namespace|User|Status|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExperienceGetStatusWithSignatureAsyncFunction* GetStatusWithSignature(
        UObject* WorldContextObject,
        FGs2ExperienceOwnStatus Status,
        FString KeyId
    );

    virtual void Activate() override;
};