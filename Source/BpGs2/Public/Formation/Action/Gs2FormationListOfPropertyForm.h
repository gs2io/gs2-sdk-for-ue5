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
#include "BpGs2/Public/Formation/Model/Gs2FormationUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FormationListOfPropertyForm.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationListOfPropertyFormSuccessDelegate, const TArray<FGs2FormationPropertyFormValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationListOfPropertyFormErrorDelegate, const TArray<FGs2FormationPropertyFormValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FormationListOfPropertyFormAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FormationOwnUser User;

public:
    FString PropertyFormModelName;

    UPROPERTY(BlueprintAssignable)
    FGs2FormationListOfPropertyFormSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2FormationListOfPropertyFormErrorDelegate OnError;

    UGs2FormationListOfPropertyFormAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::Fetch::ListOfPropertyForm", Category="Game Server Services|GS2-Formation|Namespace|User|PropertyForm|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FormationListOfPropertyFormAsyncFunction* ListOfPropertyForm(
        UObject* WorldContextObject,
        FGs2FormationOwnUser User,
        FString PropertyFormModelName
    );

    virtual void Activate() override;
};