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
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeIncrementalRateModel.h"
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeConfig.h"
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeExchange.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExchangeActionIncrementalExchange.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeIncrementalExchangeSuccessDelegate, FGs2ExchangeOwnExchange, Exchange, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeIncrementalExchangeErrorDelegate, FGs2ExchangeOwnExchange, Exchange, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExchangeIncrementalExchangeAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ExchangeOwnExchange Exchange;
    FString RateName;
    int32 Count;
    TArray<FGs2ExchangeConfig> Config;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2ExchangeIncrementalExchangeSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2ExchangeIncrementalExchangeErrorDelegate OnError;

    UGs2ExchangeIncrementalExchangeAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::Exchange::Action::IncrementalExchange", Category="Game Server Services|GS2-Exchange|Namespace|User|Exchange|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExchangeIncrementalExchangeAsyncFunction* IncrementalExchange(
        UObject* WorldContextObject,
        FGs2ExchangeOwnExchange Exchange,
        FString RateName,
        int32 Count,
        TArray<FGs2ExchangeConfig> Config
    );

    virtual void Activate() override;
};