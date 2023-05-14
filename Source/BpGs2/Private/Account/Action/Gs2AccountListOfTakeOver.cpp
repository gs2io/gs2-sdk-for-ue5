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

#include "Account/Action/Gs2AccountListOfTakeOver.h"
#include "Account/Model/Gs2AccountTakeOver.h"
#include "Core/BpGs2Constant.h"

UGs2AccountListOfTakeOverAsyncFunction::UGs2AccountListOfTakeOverAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountListOfTakeOverAsyncFunction* UGs2AccountListOfTakeOverAsyncFunction::ListOfTakeOver(
    UObject* WorldContextObject,
    FGs2AccountOwnAccount Account
)
{
    UGs2AccountListOfTakeOverAsyncFunction* Action = NewObject<UGs2AccountListOfTakeOverAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountListOfTakeOverAsyncFunction::ListOfTakeOver] Account parameter specification is missing."))
        return Action;
    }
    Action->Account = Account;
    return Action;
}

void UGs2AccountListOfTakeOverAsyncFunction::Activate()
{
    TArray<FGs2AccountTakeOverValue> ReturnTakeOvers;
    FGs2Error ReturnError;
    const auto It = Account.Value->TakeOvers(
    );
    for (auto v : *It)
    {
        ReturnTakeOvers.Add(EzTakeOverToFGs2AccountTakeOverValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnTakeOvers, ReturnError);
}