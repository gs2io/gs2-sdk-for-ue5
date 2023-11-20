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
#include "Showcase/Model/Gs2ShowcaseShowcase.h"
#include "Showcase/Model/Gs2ShowcaseShowcase.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ShowcaseShowcaseGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseShowcaseGetValueSuccessDelegate, FGs2ShowcaseShowcaseValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ShowcaseShowcaseGetValueErrorDelegate, FGs2ShowcaseShowcaseValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ShowcaseShowcaseGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ShowcaseOwnShowcase Showcase;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ShowcaseShowcaseGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ShowcaseShowcaseGetValueErrorDelegate OnError;

    UGs2ShowcaseShowcaseGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Showcase::Fetch::GetValueOfShowcase", Category="Game Server Services|GS2-Showcase|Namespace|User|Showcase|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ShowcaseShowcaseGetValueAsyncFunction* ShowcaseGetValue(
        UObject* WorldContextObject,
        FGs2ShowcaseOwnShowcase Showcase
    );

    virtual void Activate() override;
};