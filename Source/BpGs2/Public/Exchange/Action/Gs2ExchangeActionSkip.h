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
#include "Exchange/Model/Gs2ExchangeAwait.h"
#include "Exchange/Model/Gs2ExchangeAwait.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExchangeActionSkip.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeSkipSuccessDelegate, FGs2ExchangeOwnAwait, Await, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeSkipErrorDelegate, FGs2ExchangeOwnAwait, Await, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExchangeSkipAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ExchangeOwnAwait Await;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExchangeSkipSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExchangeSkipErrorDelegate OnError;

    UGs2ExchangeSkipAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::Await::Action::Skip", Category="Game Server Services|GS2-Exchange|Namespace|User|Await|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExchangeSkipAsyncFunction* Skip(
        UObject* WorldContextObject,
        FGs2ExchangeOwnAwait Await
    );

    virtual void Activate() override;
};