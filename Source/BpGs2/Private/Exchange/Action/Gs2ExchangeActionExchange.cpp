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

#include "Exchange/Action/Gs2ExchangeActionExchange.h"
#include "Core/BpGs2Constant.h"

UGs2ExchangeExchangeAsyncFunction::UGs2ExchangeExchangeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExchangeExchangeAsyncFunction* UGs2ExchangeExchangeAsyncFunction::Exchange(
    UObject* WorldContextObject,
    FGs2ExchangeOwnExchange Exchange,
    FString RateName,
    int32 Count,
    TArray<FGs2ExchangeConfig> Config
)
{
    UGs2ExchangeExchangeAsyncFunction* Action = NewObject<UGs2ExchangeExchangeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Exchange.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeExchangeAsyncFunction::Exchange] Exchange parameter specification is missing."))
        return Action;
    }
    Action->ExchangeValue = Exchange;
    Action->RateName = RateName;
    Action->Count = Count;
    Action->Config = Config;
    return Action;
}

void UGs2ExchangeExchangeAsyncFunction::Activate()
{
    if (ExchangeValue.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeExchangeAsyncFunction] Exchange parameter specification is missing."))
        return;
    }

    auto Future = ExchangeValue.Value->Exchange(
        RateName,
        Count,
        [&]
        {
            TArray<Gs2::UE5::Exchange::Model::FEzConfigPtr> r;
            for (auto v : Config)
            {
                r.Add(FGs2ExchangeConfigToEzConfig(v));
            }
            return r;
        }()
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        FGs2ExchangeOwnExchange ReturnExchange;
        ReturnExchange.Value = Result;
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnExchange, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2ExchangeOwnExchange ReturnExchange;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnExchange, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}