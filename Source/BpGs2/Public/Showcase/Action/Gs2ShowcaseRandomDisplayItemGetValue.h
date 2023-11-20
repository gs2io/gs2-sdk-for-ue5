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
#include "Showcase/Model/Gs2ShowcaseRandomDisplayItem.h"
#include "Showcase/Model/Gs2ShowcaseRandomDisplayItem.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ShowcaseRandomDisplayItemGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseRandomDisplayItemGetValueSuccessDelegate, FGs2ShowcaseRandomDisplayItemValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseRandomDisplayItemGetValueErrorDelegate, FGs2ShowcaseRandomDisplayItemValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ShowcaseOwnRandomDisplayItem RandomDisplayItem;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ShowcaseRandomDisplayItemGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ShowcaseRandomDisplayItemGetValueErrorDelegate OnError;

    UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::Fetch::GetValueOfRandomDisplayItem", Category="Game Server Services|GS2-Showcase|Namespace|User|RandomShowcase|RandomDisplayItem|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ShowcaseRandomDisplayItemGetValueAsyncFunction* RandomDisplayItemGetValue(
        UObject* WorldContextObject,
        FGs2ShowcaseOwnRandomDisplayItem RandomDisplayItem
    );

    virtual void Activate() override;
};