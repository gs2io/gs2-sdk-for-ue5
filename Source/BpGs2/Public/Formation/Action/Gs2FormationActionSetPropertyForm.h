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
#include "Formation/Model/Gs2FormationPropertyForm.h"
#include "Formation/Model/Gs2FormationSlotWithSignature.h"
#include "Formation/Model/Gs2FormationPropertyForm.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FormationActionSetPropertyForm.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationSetPropertyFormSuccessDelegate, FGs2FormationOwnPropertyForm, PropertyForm, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationSetPropertyFormErrorDelegate, FGs2FormationOwnPropertyForm, PropertyForm, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FormationSetPropertyFormAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FormationOwnPropertyForm PropertyForm;
    TArray<FGs2FormationSlotWithSignature> Slots;
    FString KeyId;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationSetPropertyFormSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationSetPropertyFormErrorDelegate OnError;

    UGs2FormationSetPropertyFormAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::PropertyForm::Action::SetPropertyForm", Category="Game Server Services|GS2-Formation|Namespace|User|PropertyForm|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FormationSetPropertyFormAsyncFunction* SetPropertyForm(
        UObject* WorldContextObject,
        FGs2FormationOwnPropertyForm PropertyForm,
        TArray<FGs2FormationSlotWithSignature> Slots,
        FString KeyId
    );

    virtual void Activate() override;
};