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
#include "Mission/Model/Gs2MissionMissionGroupModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MissionListOfMissionTaskModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionListOfMissionTaskModelSuccessDelegate, const TArray<FGs2MissionMissionTaskModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionListOfMissionTaskModelErrorDelegate, const TArray<FGs2MissionMissionTaskModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MissionListOfMissionTaskModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MissionMissionGroupModel MissionGroupModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionListOfMissionTaskModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionListOfMissionTaskModelErrorDelegate OnError;

    UGs2MissionListOfMissionTaskModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::Fetch::ListOfMissionTaskModel", Category="Game Server Services|GS2-Mission|Namespace|MissionGroupModel|MissionTaskModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MissionListOfMissionTaskModelAsyncFunction* ListOfMissionTaskModel(
        UObject* WorldContextObject,
        FGs2MissionMissionGroupModel MissionGroupModel
    );

    virtual void Activate() override;
};