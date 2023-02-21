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
#include "BpGs2/Public/Showcase/Model/Gs2ShowcaseSalesItem.h"
#include "BpGs2/Public/Showcase/Model/Gs2ShowcaseConfig.h"
#include "BpGs2/Public/Showcase/Model/Gs2ShowcaseShowcase.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ShowcaseActionBuy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseBuySuccessDelegate, FGs2ShowcaseOwnShowcase, Showcase, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseBuyErrorDelegate, FGs2ShowcaseOwnShowcase, Showcase, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ShowcaseBuyAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ShowcaseOwnShowcase Showcase;
    FString DisplayItemId;
    int32 Quantity;
    TArray<FGs2ShowcaseConfig> Config;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2ShowcaseBuySuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2ShowcaseBuyErrorDelegate OnError;

    UGs2ShowcaseBuyAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::Showcase::Action::Buy", Category="Game Server Services|GS2-Showcase|Namespace|User|Showcase|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ShowcaseBuyAsyncFunction* Buy(
        UObject* WorldContextObject,
        FGs2ShowcaseOwnShowcase Showcase,
        FString DisplayItemId,
        int32 Quantity,
        TArray<FGs2ShowcaseConfig> Config
    );

    virtual void Activate() override;
};