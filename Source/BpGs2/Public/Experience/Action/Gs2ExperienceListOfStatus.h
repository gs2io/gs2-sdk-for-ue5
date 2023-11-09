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
#include "BpGs2/Public/Experience/Model/Gs2ExperienceUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExperienceListOfStatus.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceListOfStatusSuccessDelegate, const TArray<FGs2ExperienceStatusValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceListOfStatusErrorDelegate, const TArray<FGs2ExperienceStatusValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExperienceListOfStatusAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ExperienceOwnUser User;

public:
    FString ExperienceName;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceListOfStatusSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceListOfStatusErrorDelegate OnError;

    UGs2ExperienceListOfStatusAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Experience::Fetch::ListOfStatus", Category="Game Server Services|GS2-Experience|Namespace|User|Status|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExperienceListOfStatusAsyncFunction* ListOfStatus(
        UObject* WorldContextObject,
        FGs2ExperienceOwnUser User,
        FString ExperienceName
    );

    virtual void Activate() override;
};