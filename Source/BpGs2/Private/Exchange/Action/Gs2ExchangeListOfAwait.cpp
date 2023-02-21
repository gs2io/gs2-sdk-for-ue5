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

#include "Exchange/Action/Gs2ExchangeListOfAwait.h"
#include "Exchange/Model/Gs2ExchangeAwait.h"
#include "Core/BpGs2Constant.h"

UGs2ExchangeListOfAwaitAsyncFunction::UGs2ExchangeListOfAwaitAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2ExchangeListOfAwaitAsyncFunction* UGs2ExchangeListOfAwaitAsyncFunction::ListOfAwait(
    UObject* WorldContextObject,
    FGs2ExchangeOwnUser User,
    FString RateName
)
{
    UGs2ExchangeListOfAwaitAsyncFunction* Action = NewObject<UGs2ExchangeListOfAwaitAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeListOfAwaitAsyncFunction::ListOfAwait] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->RateName = RateName;
    return Action;
}

void UGs2ExchangeListOfAwaitAsyncFunction::Activate()
{
    TArray<FGs2ExchangeAwaitValue> ReturnAwaits;
    FGs2Error ReturnError;
    const auto It = User.Value->Awaits(
        RateName
    );
    for (auto v : *It)
    {
        ReturnAwaits.Add(EzAwaitToFGs2ExchangeAwaitValue(v));
    }
    OnSuccess.Broadcast(ReturnAwaits, ReturnError);
}