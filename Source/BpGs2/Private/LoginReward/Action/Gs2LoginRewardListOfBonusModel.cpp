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

#include "LoginReward/Action/Gs2LoginRewardListOfBonusModel.h"
#include "LoginReward/Model/Gs2LoginRewardBonusModel.h"
#include "Core/BpGs2Constant.h"

UGs2LoginRewardListOfBonusModelAsyncFunction::UGs2LoginRewardListOfBonusModelAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2LoginRewardListOfBonusModelAsyncFunction* UGs2LoginRewardListOfBonusModelAsyncFunction::ListOfBonusModel(
    UObject* WorldContextObject,
    FGs2LoginRewardNamespace Namespace
)
{
    UGs2LoginRewardListOfBonusModelAsyncFunction* Action = NewObject<UGs2LoginRewardListOfBonusModelAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardListOfBonusModelAsyncFunction::ListOfBonusModel] Namespace parameter specification is missing."))
        return Action;
    }
    Action->Namespace = Namespace;
    return Action;
}

void UGs2LoginRewardListOfBonusModelAsyncFunction::Activate()
{
    TArray<FGs2LoginRewardBonusModelValue> ReturnBonusModels;
    FGs2Error ReturnError;

    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LoginRewardListOfBonusModelAsyncFunction::Activate] Namespace parameter specification is missing."))
        return;
    }
    const auto It = Namespace.Value->BonusModels(
    );
    for (auto v : *It)
    {
        ReturnBonusModels.Add(EzBonusModelToFGs2LoginRewardBonusModelValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnBonusModels, ReturnError);
}