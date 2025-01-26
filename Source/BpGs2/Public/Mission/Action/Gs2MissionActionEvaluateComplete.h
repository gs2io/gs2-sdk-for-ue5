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
#include "Mission/Model/Gs2MissionComplete.h"
#include "Mission/Model/Gs2MissionComplete.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MissionActionEvaluateComplete.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionEvaluateCompleteSuccessDelegate, FGs2MissionOwnComplete, Complete, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MissionEvaluateCompleteErrorDelegate, FGs2MissionOwnComplete, Complete, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MissionEvaluateCompleteAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MissionOwnComplete Complete;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionEvaluateCompleteSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MissionEvaluateCompleteErrorDelegate OnError;

    UGs2MissionEvaluateCompleteAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Mission::Complete::Action::EvaluateComplete", Category="Game Server Services|GS2-Mission|Namespace|User|Complete|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MissionEvaluateCompleteAsyncFunction* EvaluateComplete(
        UObject* WorldContextObject,
        FGs2MissionOwnComplete Complete
    );

    virtual void Activate() override;
};