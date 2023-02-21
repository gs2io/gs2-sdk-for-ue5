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

#include "Lottery/Action/Gs2LotteryListOfBoxItems.h"
#include "Lottery/Model/Gs2LotteryBoxItems.h"
#include "Core/BpGs2Constant.h"

UGs2LotteryListOfBoxItemsAsyncFunction::UGs2LotteryListOfBoxItemsAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LotteryListOfBoxItemsAsyncFunction* UGs2LotteryListOfBoxItemsAsyncFunction::ListOfBoxItems(
    UObject* WorldContextObject,
    FGs2LotteryOwnUser User
)
{
    UGs2LotteryListOfBoxItemsAsyncFunction* Action = NewObject<UGs2LotteryListOfBoxItemsAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryListOfBoxItemsAsyncFunction::ListOfBoxItems] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    return Action;
}

void UGs2LotteryListOfBoxItemsAsyncFunction::Activate()
{
    TArray<FGs2LotteryBoxItemsValue> ReturnBoxItemses;
    FGs2Error ReturnError;
    OnSuccess.Broadcast(ReturnBoxItemses, ReturnError);
}