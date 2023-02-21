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

#include "Lottery/Action/Gs2LotteryActionResetBox.h"
#include "Core/BpGs2Constant.h"

UGs2LotteryResetBoxAsyncFunction::UGs2LotteryResetBoxAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LotteryResetBoxAsyncFunction* UGs2LotteryResetBoxAsyncFunction::ResetBox(
    UObject* WorldContextObject,
    FGs2LotteryOwnBoxItems BoxItems
)
{
    UGs2LotteryResetBoxAsyncFunction* Action = NewObject<UGs2LotteryResetBoxAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (BoxItems.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryResetBoxAsyncFunction::ResetBox] BoxItems parameter specification is missing."))
        return Action;
    }
    Action->BoxItems = BoxItems;
    return Action;
}

void UGs2LotteryResetBoxAsyncFunction::Activate()
{
    if (BoxItems.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryResetBoxAsyncFunction] BoxItems parameter specification is missing."))
        return;
    }

    auto Future = BoxItems.Value->ResetBox(
    );
    Future->GetTask().OnSuccessDelegate().BindLambda([&](auto Result)
    {
        FGs2LotteryOwnBoxItems ReturnBoxItems;
        ReturnBoxItems.Value = Result;
        const FGs2Error ReturnError;
        OnError.Broadcast(ReturnBoxItems, ReturnError);
        SetReadyToDestroy();
    });
    Future->GetTask().OnErrorDelegate().BindLambda([&](auto Error)
    {
        FGs2LotteryOwnBoxItems ReturnBoxItems;
        FGs2Error ReturnError;
        ReturnError.Value = Error;
        OnError.Broadcast(ReturnBoxItems, ReturnError);
        SetReadyToDestroy();
    });
    Future->StartBackgroundTask();
}