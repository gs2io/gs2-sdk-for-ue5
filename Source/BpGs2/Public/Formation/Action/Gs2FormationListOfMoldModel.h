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
#include "BpGs2/Public/Formation/Model/Gs2FormationNamespace.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2FormationListOfMoldModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationListOfMoldModelSuccessDelegate, const TArray<FGs2FormationMoldModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationListOfMoldModelErrorDelegate, const TArray<FGs2FormationMoldModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FormationListOfMoldModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FormationNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationListOfMoldModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationListOfMoldModelErrorDelegate OnError;

    UGs2FormationListOfMoldModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::Fetch::ListOfMoldModel", Category="Game Server Services|GS2-Formation|Namespace|MoldModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FormationListOfMoldModelAsyncFunction* ListOfMoldModel(
        UObject* WorldContextObject,
        FGs2FormationNamespace Namespace
    );

    virtual void Activate() override;
};