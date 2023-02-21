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
#include "BpGs2/Public/Formation/Model/Gs2FormationForm.h"
#include "BpGs2/Public/Formation/Model/Gs2FormationForm.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FormationActionGetFormWithSignature.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationGetFormWithSignatureSuccessDelegate, FGs2FormationOwnForm, Form, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationGetFormWithSignatureErrorDelegate, FGs2FormationOwnForm, Form, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FormationGetFormWithSignatureAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FormationOwnForm Form;
    FString KeyId;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2FormationGetFormWithSignatureSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2FormationGetFormWithSignatureErrorDelegate OnError;

    UGs2FormationGetFormWithSignatureAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::Form::Action::GetFormWithSignature", Category="Game Server Services|GS2-Formation|Namespace|User|Mold|Form|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FormationGetFormWithSignatureAsyncFunction* GetFormWithSignature(
        UObject* WorldContextObject,
        FGs2FormationOwnForm Form,
        FString KeyId
    );

    virtual void Activate() override;
};