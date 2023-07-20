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

#include "Enchant/Action/Gs2EnchantListOfBalanceParameterStatus.h"
#include "Enchant/Model/Gs2EnchantBalanceParameterStatus.h"
#include "Core/BpGs2Constant.h"

UGs2EnchantListOfBalanceParameterStatusAsyncFunction::UGs2EnchantListOfBalanceParameterStatusAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2EnchantListOfBalanceParameterStatusAsyncFunction* UGs2EnchantListOfBalanceParameterStatusAsyncFunction::ListOfBalanceParameterStatus(
    UObject* WorldContextObject,
    FGs2EnchantOwnUser User,
    FString ParameterName
)
{
    UGs2EnchantListOfBalanceParameterStatusAsyncFunction* Action = NewObject<UGs2EnchantListOfBalanceParameterStatusAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantListOfBalanceParameterStatusAsyncFunction::ListOfBalanceParameterStatus] User parameter specification is missing."))
        return Action;
    }
    Action->User = User;
    Action->ParameterName = ParameterName;
    return Action;
}

void UGs2EnchantListOfBalanceParameterStatusAsyncFunction::Activate()
{
    TArray<FGs2EnchantBalanceParameterStatusValue> ReturnBalanceParameterStatuses;
    FGs2Error ReturnError;

    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantListOfBalanceParameterStatusAsyncFunction::Activate] User parameter specification is missing."))
        return;
    }
    const auto It = User.Value->BalanceParameterStatuses(
        ParameterName
    );
    for (auto v : *It)
    {
        ReturnBalanceParameterStatuses.Add(EzBalanceParameterStatusToFGs2EnchantBalanceParameterStatusValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnBalanceParameterStatuses, ReturnError);
}