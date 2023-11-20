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
#include "Formation/Model/Gs2FormationForm.h"
#include "Formation/Model/Gs2FormationForm.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FormationFormGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationFormGetValueSuccessDelegate, FGs2FormationFormValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationFormGetValueErrorDelegate, FGs2FormationFormValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FormationFormGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FormationOwnForm Form;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationFormGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationFormGetValueErrorDelegate OnError;

    UGs2FormationFormGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::Fetch::GetValueOfForm", Category="Game Server Services|GS2-Formation|Namespace|User|Mold|Form|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FormationFormGetValueAsyncFunction* FormGetValue(
        UObject* WorldContextObject,
        FGs2FormationOwnForm Form
    );

    virtual void Activate() override;
};