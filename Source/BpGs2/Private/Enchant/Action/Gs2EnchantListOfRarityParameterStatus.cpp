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

#include "Enchant/Action/Gs2EnchantListOfRarityParameterStatus.h"
#include "Enchant/Model/Gs2EnchantRarityParameterStatus.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantListOfRarityParameterStatusAsyncFunction::UGs2EnchantListOfRarityParameterStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantListOfRarityParameterStatusAsyncFunction* UGs2EnchantListOfRarityParameterStatusAsyncFunction::ListOfRarityParameterStatus(
    UObject* WorldContextObject,
    FGs2EnchantOwnUser User,
    FString ParameterName
)
{
    UGs2EnchantListOfRarityParameterStatusAsyncFunction* Action = NewObject<UGs2EnchantListOfRarityParameterStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantListOfRarityParameterStatusAsyncFunction::ListOfRarityParameterStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->ParameterName = ParameterName;
    return Action;
}

void UGs2EnchantListOfRarityParameterStatusAsyncFunction::Activate()
{
    TArray<FGs2EnchantRarityParameterStatusValue> ReturnRarityParameterStatuses;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantListOfRarityParameterStatusAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->RarityParameterStatuses(
        ParameterName
    );
    for (auto v : *It)
    {
        ReturnRarityParameterStatuses.Add(EzRarityParameterStatusToFGs2EnchantRarityParameterStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnRarityParameterStatuses, ReturnError);
}