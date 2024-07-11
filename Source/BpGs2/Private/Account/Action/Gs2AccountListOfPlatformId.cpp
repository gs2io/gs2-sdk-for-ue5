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

#include "Account/Action/Gs2AccountListOfPlatformId.h"
#include "Account/Model/Gs2AccountPlatformId.h"
#include "Core/BpGs2Constant.h"

UGs2AccountListOfPlatformIdAsyncFunction::UGs2AccountListOfPlatformIdAsyncFunction(
    const FObjectInitializer& ObjectInitializer
): Super(ObjectInitializer)
{
    
}

UGs2AccountListOfPlatformIdAsyncFunction* UGs2AccountListOfPlatformIdAsyncFunction::ListOfPlatformId(
    UObject* WorldContextObject,
    FGs2AccountOwnAccount Account
)
{
    UGs2AccountListOfPlatformIdAsyncFunction* Action = NewObject<UGs2AccountListOfPlatformIdAsyncFunction>();
    Action->RegisterWithGameInstance(WorldContextObject);
    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountListOfPlatformIdAsyncFunction::ListOfPlatformId] Account parameter specification is missing."))
        return Action;
    }
    Action->Account = Account;
    return Action;
}

void UGs2AccountListOfPlatformIdAsyncFunction::Activate()
{
    TArray<FGs2AccountPlatformIdValue> ReturnPlatformIds;
    FGs2Error ReturnError;

    if (Account.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2AccountListOfPlatformIdAsyncFunction::Activate] Account parameter specification is missing."))
        return;
    }
    const auto It = Account.Value->PlatformIds(
    );
    for (auto v : *It)
    {
        ReturnPlatformIds.Add(EzPlatformIdToFGs2AccountPlatformIdValue(v->Current()));
    }
    OnSuccess.Broadcast(ReturnPlatformIds, ReturnError);
}