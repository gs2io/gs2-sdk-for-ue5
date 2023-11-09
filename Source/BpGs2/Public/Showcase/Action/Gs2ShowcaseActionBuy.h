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
#include "BpGs2/Public/Showcase/Model/Gs2ShowcaseDisplayItem.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ShowcaseActionBuy.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseBuySuccessDelegate, FGs2ShowcaseOwnDisplayItem, DisplayItem, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseBuyErrorDelegate, FGs2ShowcaseOwnDisplayItem, DisplayItem, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ShowcaseBuyAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ShowcaseOwnDisplayItem DisplayItem;
    int32 Quantity;
    TArray<FGs2ShowcaseConfig> Config;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ShowcaseBuySuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ShowcaseBuyErrorDelegate OnError;

    UGs2ShowcaseBuyAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::DisplayItem::Action::Buy", Category="Game Server Services|GS2-Showcase|Namespace|User|Showcase|DisplayItem|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ShowcaseBuyAsyncFunction* Buy(
        UObject* WorldContextObject,
        FGs2ShowcaseOwnDisplayItem DisplayItem,
        int32 Quantity,
        TArray<FGs2ShowcaseConfig> Config
    );

    virtual void Activate() override;
};