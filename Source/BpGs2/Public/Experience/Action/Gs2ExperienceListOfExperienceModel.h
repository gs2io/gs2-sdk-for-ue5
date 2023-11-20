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
#include "Experience/Model/Gs2ExperienceNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExperienceListOfExperienceModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceListOfExperienceModelSuccessDelegate, const TArray<FGs2ExperienceExperienceModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExperienceListOfExperienceModelErrorDelegate, const TArray<FGs2ExperienceExperienceModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExperienceListOfExperienceModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ExperienceNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceListOfExperienceModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExperienceListOfExperienceModelErrorDelegate OnError;

    UGs2ExperienceListOfExperienceModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Experience::Fetch::ListOfExperienceModel", Category="Game Server Services|GS2-Experience|Namespace|ExperienceModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExperienceListOfExperienceModelAsyncFunction* ListOfExperienceModel(
        UObject* WorldContextObject,
        FGs2ExperienceNamespace Namespace
    );

    virtual void Activate() override;
};