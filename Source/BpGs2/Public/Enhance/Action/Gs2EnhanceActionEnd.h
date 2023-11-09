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
#include "BpGs2/Public/Enhance/Model/Gs2EnhanceProgress.h"
#include "BpGs2/Public/Enhance/Model/Gs2EnhanceConfig.h"
#include "BpGs2/Public/Enhance/Model/Gs2EnhanceProgress.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2EnhanceActionEnd.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceEndSuccessDelegate, FGs2EnhanceOwnProgress, Progress, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2EnhanceEndErrorDelegate, FGs2EnhanceOwnProgress, Progress, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2EnhanceEndAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2EnhanceOwnProgress Progress;
    TArray<FGs2EnhanceConfig> Config;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceEndSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2EnhanceEndErrorDelegate OnError;

    UGs2EnhanceEndAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Enhance::Progress::Action::End", Category="Game Server Services|GS2-Enhance|Namespace|User|Progress|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2EnhanceEndAsyncFunction* End(
        UObject* WorldContextObject,
        FGs2EnhanceOwnProgress Progress,
        TArray<FGs2EnhanceConfig> Config
    );

    virtual void Activate() override;
};