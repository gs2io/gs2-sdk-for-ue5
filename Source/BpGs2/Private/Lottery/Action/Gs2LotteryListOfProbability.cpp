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

#include "Lottery/Action/Gs2LotteryListOfProbability.h"
#include "Lottery/Model/Gs2LotteryProbability.h"
#include "Core/BpGs2Constant.h"

UGs2LotteryListOfProbabilityAsyncFunction::UGs2LotteryListOfProbabilityAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LotteryListOfProbabilityAsyncFunction* UGs2LotteryListOfProbabilityAsyncFunction::ListOfProbability(
    UObject* WorldContextObject,
    FGs2LotteryOwnUser User,
    FString LotteryName
)
{
    UGs2LotteryListOfProbabilityAsyncFunction* Action = NewObject<UGs2LotteryListOfProbabilityAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryListOfProbabilityAsyncFunction::ListOfProbability] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->LotteryName = LotteryName;
    return Action;
}

void UGs2LotteryListOfProbabilityAsyncFunction::Activate()
{
    TArray<FGs2LotteryProbability> ReturnProbabilities;
    FGs2Error ReturnError;
    const auto It = User.Value->Probabilities(
        LotteryName
    );
    for (auto v : *It)
    {
        ReturnProbabilities.Add(EzProbabilityToFGs2LotteryProbability(v));
    }
    OnSuccess.Broadcast(ReturnProbabilities, ReturnError);
}