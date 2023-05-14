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

#include "Lottery/Action/Gs2LotteryListOfLotteryModel.h"
#include "Lottery/Model/Gs2LotteryLotteryModel.h"
#include "Core/BpGs2Constant.h"

UGs2LotteryListOfLotteryModelAsyncFunction::UGs2LotteryListOfLotteryModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LotteryListOfLotteryModelAsyncFunction* UGs2LotteryListOfLotteryModelAsyncFunction::ListOfLotteryModel(
    UObject* WorldContextObject,
    FGs2LotteryNamespace Namespace
)
{
    UGs2LotteryListOfLotteryModelAsyncFunction* Action = NewObject<UGs2LotteryListOfLotteryModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LotteryListOfLotteryModelAsyncFunction::ListOfLotteryModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2LotteryListOfLotteryModelAsyncFunction::Activate()
{
    TArray<FGs2LotteryLotteryModelValue> ReturnLotteryModels;
    FGs2Error ReturnError;
    const auto It = Namespace.Value->LotteryModels(
    );
    for (auto v : *It)
    {
        ReturnLotteryModels.Add(EzLotteryModelToFGs2LotteryLotteryModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnLotteryModels, ReturnError);
}