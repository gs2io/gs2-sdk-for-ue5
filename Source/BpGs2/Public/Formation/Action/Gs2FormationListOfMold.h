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
#include "Gs2FormationListOfMold.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationListOfMoldSuccessDelegate, const TArray<FGs2FormationMoldValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2FormationListOfMoldErrorDelegate, const TArray<FGs2FormationMoldValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2FormationListOfMoldAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2FormationOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationListOfMoldSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2FormationListOfMoldErrorDelegate OnError;

    UGs2FormationListOfMoldAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Formation::Fetch::ListOfMold", Category="Game Server Services|GS2-Formation|Namespace|User|Mold|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2FormationListOfMoldAsyncFunction* ListOfMold(
        UObject* WorldContextObject,
        FGs2FormationOwnUser User
    );

    virtual void Activate() override;
};