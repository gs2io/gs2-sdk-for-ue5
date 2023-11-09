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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeRateModel.h"
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeConfig.h"
#include "BpGs2/Public/Exchange/Model/Gs2ExchangeExchange.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ExchangeActionExchange.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeExchangeSuccessDelegate, FGs2ExchangeOwnExchange, Exchange, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ExchangeExchangeErrorDelegate, FGs2ExchangeOwnExchange, Exchange, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ExchangeExchangeAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    UPARAM(DisplayName="Exchange") FGs2ExchangeOwnExchange ExchangeValue;
    FString RateName;
    int32 Count;
    TArray<FGs2ExchangeConfig> Config;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExchangeExchangeSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ExchangeExchangeErrorDelegate OnError;

    UGs2ExchangeExchangeAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Exchange::Exchange::Action::Exchange", Category="Game Server Services|GS2-Exchange|Namespace|User|Exchange|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ExchangeExchangeAsyncFunction* Exchange(
        UObject* WorldContextObject,
        FGs2ExchangeOwnExchange ExchangeValue,
        FString RateName,
        int32 Count,
        TArray<FGs2ExchangeConfig> Config
    );

    virtual void Activate() override;
};