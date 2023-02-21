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

#include "Lottery/Action/Gs2LotteryBoxItemsGetValue.h"
#include "Core/BpGs2Constant.h"

UGs2LotteryBoxItemsGetValueAsyncFunction::UGs2LotteryBoxItemsGetValueAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LotteryBoxItemsGetValueAsyncFunction* UGs2LotteryBoxItemsGetValueAsyncFunction::BoxItemsGetValue(
    UObject* WorldContextObject,
    FGs2LotteryOwnBoxItems BoxItems
)
{
    UGs2LotteryBoxItemsGetValueAsyncFunction* Action = NewObject<UGs2LotteryBoxItemsGetValueAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BoxItems.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryBoxItemsGetValueAsyncFunction::BoxItemsGetValue] BoxItems parameter specification is missing."))
        return Action;
    }
    Action->BoxItems = BoxItems;
    return Action;
}

void UGs2LotteryBoxItemsGetValueAsyncFunction::Activate()
{
    auto Future = BoxItems.Value->Model(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](const auto Result)
    {
        auto ReturnValue = EzBoxItemsToFGs2LotteryBoxItemsValue(Result);
        const FGs2Error ReturnError;
        OnSuccess.Broadcast(ReturnValue, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](const auto Error)
    {
        FGs2LotteryBoxItemsValue ReturnBoxItems;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBoxItems, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}