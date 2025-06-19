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

#include "Exchange/Action/Gs2ExchangeActionIncrementalExchange.h"
#include "Core/BpGs2Constant.h"

UGs2ExchangeIncrementalExchangeAsyncFunction::UGs2ExchangeIncrementalExchangeAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExchangeIncrementalExchangeAsyncFunction* UGs2ExchangeIncrementalExchangeAsyncFunction::IncrementalExchange(
    UObject* WorldContextObject,
    FGs2ExchangeOwnExchange Exchange,
    FString RateName,
    int32 Count,
    TArray<FGs2ExchangeConfig> Config
)
{
    UGs2ExchangeIncrementalExchangeAsyncFunction* Action = NewObject<UGs2ExchangeIncrementalExchangeAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Exchange.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeIncrementalExchangeAsyncFunction::IncrementalExchange] Exchange parameter specification is missing."))
        return Action;
    }
    Action->Exchange = Exchange;
    Action->RateName = RateName;
    Action->Count = Count;
    Action->Config = Config;
    return Action;
}

void UGs2ExchangeIncrementalExchangeAsyncFunction::Activate()
{
    if (Exchange.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeIncrementalExchangeAsyncFunction] Exchange parameter specification is missing."))
        return;
    }

    auto Future = Exchange.Value->IncrementalExchange(
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
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2CoreOwnTransaction ReturnTransaction;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnTransaction, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}